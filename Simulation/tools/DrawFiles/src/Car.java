import java.awt.Color;
import java.util.AbstractList;
import java.util.ArrayList;
import java.util.List;

import processing.core.PApplet;
import processing.core.PConstants;

public class Car {
  Color c;
  float xpos;
  float ypos;
  float xspeed;
  float carSize;
  Agent carAgent;
  List<Point> allPath;
  PApplet parent; // The parent PApplet that we will render ourselves onto
  
  int listIndex=0;


  public Car(Agent oAgent, float tempcarSize, float tempXspeed,PApplet p) { 
    parent = p;
    c = random_color(254);
    carSize = tempcarSize;
    xspeed = tempXspeed;
    carAgent = oAgent;	
	getAgentPath();
  }  
  private void getAgentPath() {
	  allPath = new ArrayList<Point>();
	  int pathIndex;
	  float offset = this.carSize *3/4;
	  
	  for(pathIndex=0;pathIndex<=carAgent.path.size()-2;pathIndex++) {

		  Node fromNode = carAgent.path.get(pathIndex);
		  Node toNode = carAgent.path.get(pathIndex+1);
		  float x1 = fromNode.longitude;
		  float x2 = toNode.longitude;
		  float y1 = fromNode.latitude;
		  float y2 = toNode.latitude;
		  double slope = (y2-y1)/(x2-x1);
		  
		  Double L = Math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		  float offsetPixels;
		  //get road width by 4
		  if(Math.toDegrees(Math.atan(slope))>Math.toDegrees(90)) {
			  offsetPixels=carSize*5/4;
		  } else {
			  offsetPixels=-carSize*3/4;
		  }
		  // This is the first parallel line
		  float x1p1 = x1 + offsetPixels * (y2-y1) / L.floatValue();
		  float x2p1 = x2 + offsetPixels * (y2-y1) / L.floatValue();
		  float y1p1 = y1 + offsetPixels * (x1-x2) / L.floatValue();
		  float y2p1 = y2 + offsetPixels * (x1-x2) / L.floatValue();
		  
		  Point P1 = new Point(x1p1,y1p1);
		  Point P2 = new Point(x2p1,y2p1);
		  if(!(P1.X==P2.X && P1.Y==P2.Y)) {
		  List<Point> gP = GetPoints(P1, P2);
		  allPath = new CompositeUnmodifiableList<Point>(allPath,gP);
		  }
	  }
	  if(carAgent.path.size()==1 || allPath.size()==0) {
		  List<Point> tempList = new ArrayList<Point>();
		  Node singleNode = carAgent.path.get(0);
		  Point singlePoint = new Point(singleNode.longitude+offset,singleNode.latitude+offset);
		  tempList.add(singlePoint);
		  allPath = new CompositeUnmodifiableList<Point>(allPath,tempList);
	  }
		
  }
  private Color random_color(int v){
	  return new Color((int) parent.random(v),(int)  parent.random(v),(int)  parent.random(v));      
	}
  public void display() {
	  
	    float xpr=0,ypr=0,slope;
	    double angle;
	    if(listIndex>1) {
		  	Point prevPos = allPath.get(listIndex-1);
		  	xpr = (float) prevPos.X;
		  	ypr = (float) prevPos.Y;
		  	if(xpos!=xpr) {
		  	slope=(ypos-ypr)/(xpos-xpr);
		  	angle = Math.atan(slope);
		  	} else {
		  		angle = Math.PI/2;
		  	}
			  
		    parent.pushMatrix();
		    parent.stroke(0);
		    parent.fill(c.getRed(),c.getGreen(),c.getBlue());
		    parent.rectMode(PConstants.CENTER);
		    parent.translate(xpos, ypos);
		    parent.rotate((float) angle);
		    
		    parent.rect(0,0,carSize*2,carSize);
		    parent.rotate(-(float) angle);
		    parent.fill(255);
		    parent.textFont(parent.createFont("serif Bold",carSize - 8));
		    parent.textAlign(PConstants.CENTER,PConstants.CENTER);
		    parent.text(carAgent.agtID,0,0,carSize/2);
		    parent.popMatrix();
		  	
	    
	    } else {
	    	parent.pushMatrix();
		    parent.stroke(0);
		    parent.fill(c.getRed(),c.getGreen(),c.getBlue());
		    parent.rectMode(PConstants.CENTER);
		    parent.translate(xpos, ypos);
		    
		    
		    parent.rect(0,0,carSize*2,carSize);
		    
		    parent.fill(255);
		    parent.textFont(parent.createFont("serif Bold",carSize - 8));
		    parent.textAlign(PConstants.CENTER,PConstants.CENTER);
		    parent.text(carAgent.agtID,0,0,carSize/2);
		    parent.popMatrix();
	    }
	    
	  	if(listIndex!=allPath.size()-1) {
	  	listIndex++;
	  	}

	  }
  
 
  public  void drive() {
	  
	   
	  	Point currPos = allPath.get(listIndex);
	  	xpos = (float) currPos.X;
	  	ypos = (float) currPos.Y;

			
	  }
  
  public List<Point> GetPoints(Point p1, Point p2)
  {
	  double y;
	  double slope = (p2.Y-p1.Y)/(p2.X-p1.X);
      double intercept = p1.Y - (slope*p1.X);
      double j;
      List<Point> points = new ArrayList<Point>();
      if(p1.X == p2.X) {
    	  for (y = p1.Y; y <= p2.Y; )
          {
    		  
              Point p = new Point(p1.X, y);
              points.add(p);
              y= y+parent.random(100);
          }
      }else if(p1.X < p2.X) {
    	  for(j=p1.X;j<=p2.X;) {
    		  
    		  y = slope*j + intercept;
    		  //j=j+(p2.X-p1.X)/10;
    		  Point p = new Point(j, y);
              points.add(p);
              j=j+parent.random(80);
    	  }
      } else {
    	  for(j=p1.X;j>=p2.X;) {
    		  y = slope*j + intercept;
    		  //j=j+(p1.X-p2.X)/10;
    		  Point p = new Point(j, y);
              points.add(p);
              j=j-parent.random(100);
    	  }
      }
     

      return points;
  }
  
  
  
  
}
class CompositeUnmodifiableList<E> extends AbstractList<E> {

    private final List<E> list1;
    private final List<E> list2;

    public CompositeUnmodifiableList(List<E> list1, List<E> list2) {
        this.list1 = list1;
        this.list2 = list2;
    }

    @Override
    public E get(int index) {
        if (index < list1.size()) {
            return list1.get(index);
        }
        return list2.get(index-list1.size());
    }

    @Override
    public int size() {
        return list1.size() + list2.size();
    }
}