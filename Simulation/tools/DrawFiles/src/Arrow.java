import java.util.ArrayList;
import java.util.List;

import processing.core.PApplet;

public class Arrow {
	Edge oEdge;
	float roadWidth;
	PApplet parent;
	
	public Arrow(Edge coEdge, float croadWidth, PApplet p) {
		oEdge = coEdge;
		roadWidth = croadWidth;
		parent = p;
	}
	
	public void display() {
		
		if(oEdge.fromNode.ID==oEdge.toNode.ID) {
			return;
		}
		List<Point> centerPoints = getPath(0);
		List<Point> leftPoints = getPath(-1);
		List<Point> rightPoints = getPath(1);
		parent.stroke(255);
		parent.strokeWeight(5);
		parent.fill(102,0,0);
		
		int i;
		int midpoint;
		
		if(centerPoints.size()==0) {
			return;
		}
		if (centerPoints.size() % 2 == 0) {
		    midpoint = centerPoints.size()/2;
			//System.out.println("test data:"+midpoint);
		}
		else {
		    midpoint =  (centerPoints.size()+1)/2;
		    //System.out.println("test data:"+midpoint);
		}
			i=midpoint;
			int triangleOffset = 40;
			float X1 = (float)leftPoints.get(i-triangleOffset).X;
			float Y1 = (float)leftPoints.get(i-triangleOffset).Y;
			float X2=(float)centerPoints.get(i).X;
			float Y2=(float)centerPoints.get(i).Y;
			float X3=(float)rightPoints.get(i-triangleOffset).X;
			float Y3=(float)rightPoints.get(i-triangleOffset).Y;
			parent.triangle(X1,Y1,X2,Y2,X3,Y3);
	}
	
	private List<Point> getPath(int index) { //index 0 for center; -1 for left; 1 for right
		  //List<Point> allPath = new ArrayList<Point>();
		 
	  
		  Node fromNode = oEdge.fromNode;
		  Node toNode = oEdge.toNode;
		  float x1 = fromNode.longitude;
		  float x2 = toNode.longitude;
		  float y1 = fromNode.latitude;
		  float y2 = toNode.latitude;
		  double slope, angle;
		  if(x1!=x2) {
			  slope = (y2-y1)/(x2-x1);
			  	angle = Math.atan(slope);
			  	} else {
			  		angle = Math.PI/2;
			  	}
		  Double L = Math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		  float offsetPixels=0;
		  if(Math.toDegrees(angle)>Math.toDegrees(90)) {
			  if (index==0){
				  offsetPixels=roadWidth*6/10;
			  }
			  else if(index==1){
				  offsetPixels=roadWidth*11/10;
			  }
			  else if(index==-1){
				  offsetPixels=roadWidth*1/10;
			  }
			  
		  } else {
			  
			  if (index==0){
				  offsetPixels=-roadWidth*6/10;
			  }
			  else if(index==1){
				  offsetPixels=-roadWidth*11/10;
			  }
			  else if(index==-1){
				  offsetPixels=-roadWidth*1/10;
			  }
		  }
		  
		  // This is the first parallel line
		  float x1p1 = x1 + offsetPixels * (y2-y1) / L.floatValue();
		  float x2p1 = x2 + offsetPixels * (y2-y1) / L.floatValue();
		  float y1p1 = y1 + offsetPixels * (x1-x2) / L.floatValue();
		  float y2p1 = y2 + offsetPixels * (x1-x2) / L.floatValue();
//		  if(oEdge.edgeID==16) {
//			  System.out.println("testing");
//		  }
		 
		  Point P1 = new Point(x1p1,y1p1);
		  Point P2 = new Point(x2p1,y2p1);
		  List<Point> gP = GetPoints(P1, P2);
		  return gP;
	      
	}
//	private Point getThreeFourthPoint(Point P1,Point P2) {
//		List<Point> allPath = new ArrayList<Point>();
//		allPath = GetPoints(P1, P2);  
//		if(allPath.size()>0) {
//			   return allPath.get(3*allPath.size()/4);
//			   } else {
//				   return new Point(P1.X,P1.Y);
//			   }
//	}
	 public List<Point> GetPoints(Point p1, Point p2)
	  {
		  double y;
		  double slope;
		  List<Point> points = new ArrayList<Point>();
		  
		  if(p1.X==p2.X){
			  if(p1.Y<p2.Y) {
			  for (y = p1.Y; y <= p2.Y;y++ )
	          {
	              Point p = new Point(p1.X, y);
	              points.add(p);
	           
	          } 
			  }else {
				  for (y = p1.Y; y >= p2.Y;y-- )
		          {
		              Point p = new Point(p1.X, y);
		              points.add(p);
		              
		          } 
			  }
		  }else {
		  slope= (p2.Y-p1.Y)/(p2.X-p1.X);
	      double intercept = p1.Y - (slope*p1.X);
	      double j;
	       if(p1.X < p2.X) {
	    	  for(j=p1.X;j<=p2.X;j++) {
	    		  y = slope*j + intercept;
	    		  //j=j+(p2.X-p1.X)/10;
	    		  Point p = new Point(j, y);
	              points.add(p);
	              
	    	  }
	      } else {
	    	  for(j=p1.X;j>=p2.X;j--) {
	    		  y = slope*j + intercept;
	    		  //j=j+(p1.X-p2.X)/10;
	    		  Point p = new Point(j, y);
	              points.add(p);
	              
	    	  }
	      }
	     

	    
	  }
		  return points;
}
}


