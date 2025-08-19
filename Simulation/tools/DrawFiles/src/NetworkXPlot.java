import java.awt.Color;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.io.BufferedReader;
import java.io.FileReader;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import controlP5.*;
import org.gicentre.utils.move.*;
import processing.core.PApplet;
import processing.core.PVector;

public class NetworkXPlot extends PApplet{
	
	public Map<Integer,Node> lstNodes;
	public Map<Integer,Edge> lstEdge;
	public Map<Integer,Double> lstProb;
	public Map<Integer,Agent> lstAgt;
	public String csvPath;
	public NetworkXPlot myPlot;
	//public Car Cars[];
	//public callOut callOuts[];
	public Arrow Arrows[];
	boolean initialize = false;
	ControlP5 cp5;
	ListBox l;
	ListBox l1; //listbox for drawing road by agent capacity or probability
	int cnt,cnt1 = 0;
	boolean bool=true;
	
	Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
	// the screen height
	Double screenheight=screenSize.getHeight();
	
	// the screen width
	Double screenwidth=screenSize.getWidth();
	
	
	ZoomPan zoomer;    // This should be declared outside any methods.
	PVector mousePos;  // Stores the mouse position.
	                   // For pretty formatting of mouse coordinates.
	NumberFormat formatter = new DecimalFormat("#.0");
	private PlotProperties oPlotProp;
	
	private  float roadWidth = 100;//Minimum 50 for resolution
	private  float scale = 500;
	private int speed = 1;
	public NetworkXPlot(){
		
	}
	public NetworkXPlot(String[] args) {
		PApplet.main("NetworkXPlot",args);
	}
	private boolean readCSV(String path) {
		try {
			List<String> csvData = readFile(path);
			
			lstNodes = readNodes(csvData);
			readProb(csvData);
			lstEdge = readEdges(csvData);
			readAgt(csvData);
			
			
			return true;
		}catch(Exception e) {
			return false;
		}
	}
	
	public void settings(){

		
	    size(screenwidth.intValue(),screenheight.intValue());
	    
		
	  
	}

	public void setup(){

		this.myPlot = new NetworkXPlot();
		this.oPlotProp = new PlotProperties(args);
		if(oPlotProp.propertyError==true) {
			System.exit(0);
		}
		this.myPlot.readCSV(oPlotProp.filename);
		
		cp5 = new ControlP5(this);
		cp5.setAutoDraw(false);
		l = cp5.addListBox("nodeFilters");
		cp5.addButton("SaveFile")
	     .setValue(0)
	     .setPosition(100,50)
	     .updateSize()
	     ;
		l1 = cp5.addListBox("edgeFilters");
		stroke(0, 128, 0);

		zoomer = new ZoomPan(this);  
	  
		zoomer.setMouseMask(SHIFT);  // Only zoom if the shift key is down.
		
		int i = 0;
		Arrows = new Arrow[this.myPlot.lstEdge.size()];
		for(Edge oEdge:this.myPlot.lstEdge.values()) {
			Arrows[i] = new Arrow(oEdge, roadWidth, this);
			
			i++;
		}
		
		
//		i=0;
//		Cars = new Car[this.myPlot.lstAgt.size()];
//		float carSize = (this.myPlot.roadWidth/3);
//		for(Agent oAgent: this.myPlot.lstAgt.values()) {
//			Cars[i]  = new Car(oAgent,carSize,this.myPlot.speed,this);
//			i++;
//		}
//		i=0;
//		callOuts = new callOut[this.myPlot.lstNodes.size()];
//		for(Node oNode:this.myPlot.lstNodes.values()) {
//			callOuts[i] = new callOut(oNode, roadWidth, this);
//			i++;
//		}
		

			
	}

	public void draw(){
		//clear();
		
		
		background(224,224,224);
		
		if(bool) {
		fill(0);
		quad(width-200,5,width-5,5,width-5,70,width-200,70);
		fill(255);
		textAlign(LEFT, TOP);
		textSize(10);
		text("ZOOM IN: SHIFT + Scroll down" + "\n" + "ZOOM OUT: SHIFT + Scroll up"+"\n"+"R: reset zoom to untransformed view",width-190,10);
		} 
		drawFilters();
		drawEdgeFilters();
		
		zoomer.transform(); // Enable the zooming/panning.
		
		
		fitAllIn();	
		
		for(Edge oEdge: this.myPlot.lstEdge.values()){
			Color c = oEdge.getEdgeColor(oPlotProp);
			if(oPlotProp.eSize.toString().equals("Capacity")) {
				cnt1 = 1;
			}
			int strokeWeight=0;
			if(cnt1==0) {
				strokeWeight= (int) (50*oEdge.probability*0.02/oPlotProp.eShapeVal);
			} else if(cnt1 == 1 ) {
				strokeWeight= oEdge.agtCapacity;
			}
			//Add Roads - Two Lanes
			if(strokeWeight==0) {
				stroke(0);
				drawDashLine(oEdge.fromNode.longitude,oEdge.fromNode.latitude,oEdge.toNode.longitude,oEdge.toNode.latitude,c);
			} else {
			fill(c.getRed(),c.getGreen(),c.getBlue());
			drawRoad(oEdge.fromNode.longitude,oEdge.fromNode.latitude,oEdge.toNode.longitude,oEdge.toNode.latitude, strokeWeight,c);
			}
		}
			
		//Adding nodes
		for(Node oNode: this.myPlot.lstNodes.values()){
			
            //fill(0);
			//ellipse(oNode.longitude,oNode.latitude,2*roadWidth,2*roadWidth);
			float xroadWidth = (float) (oPlotProp.nSizeVal * roadWidth);
			Color c = oNode.getNodeColor(oPlotProp);
			fill(c.getRed(),c.getGreen(),c.getBlue());//Drawing Roundabout road
			if(oPlotProp.nShape.toString().equals("Circle")) {
				ellipse(oNode.longitude,oNode.latitude,2*xroadWidth,2*xroadWidth);	
			} else if(oPlotProp.nShape.toString().equals("Triangle")) {
				triangle(oNode.longitude-0.7f*xroadWidth,oNode.latitude+0.7f*xroadWidth,oNode.longitude,oNode.latitude-0.7f*xroadWidth,oNode.longitude+0.7f*xroadWidth,oNode.latitude+0.7f*xroadWidth);
			} else if(oPlotProp.nShape.toString().equals("Square")) {
				rect(oNode.longitude-0.7f*xroadWidth,oNode.latitude-0.7f*xroadWidth,1.44f*xroadWidth,1.44f*xroadWidth);
			}
		    fill(255,255,255);
		    textFont(createFont("serif Bold",xroadWidth));   
		    textAlign(CENTER,CENTER);
		    if(oPlotProp.nLabel.toString().equals("Safety")) {
		    	cnt = 0;
		    } else if(oPlotProp.nLabel.toString().equals("nodeID")) {
		    	cnt = 1;
		    } else if(oPlotProp.nLabel.toString().equals("Capacity")) {
		    	cnt = 2;
		    }
		    text(oNode.getNodeByFilter(cnt),oNode.longitude,oNode.latitude);
		    
		}
		
		
	   int i;
	   
//	   
		for (i=0;i<Arrows.length;i++){
			Arrows[i].display();
		}
		
//		for (i=0;i<Cars.length;i++){
//			Cars[i].drive();
//			Cars[i].display();
//		}
		
//		if(zoomer.getZoomScale()>=0.81) { 
//			for(i=0;i<callOuts.length;i++) {
//				callOuts[i].display();
//			}
//		}

		if(bool==false) {
			save("file.png");
			bool=true;
			l.setVisible(true);
			cp5.setVisible(true);
		}
		
		
		
    }
	
	
	
	// Reset the zoom to its untransformed view if the 'R' key is pressed.
	
//	public void keyPressed()
//	{
//	  if (key== 'r')
//	  {
//		  int i;
//			for (i=0;i<Cars.length;i++){
//				Cars[i].listIndex=0;
//				
//			}
//	  }
//	}


	private void drawDashLine(float x1, float y1, float x2, float y2, Color c) {
		if(x1==x2 && y1==y2) {
			
		} else {
		List<Point> withOffset = getPointWithOffset(x1, y1, x2, y2, roadWidth/2);
		//List<Point> withOutOffset = getPointWithOffset(x1, y1, x2, y2, 0);
		int withMidpoint = (int) withOffset.size()/2;
		//int withoutMidpoint = (int) withOutOffset.size()/2;
		if(withOffset.size()>0) {
			for(int i=0; i<withOffset.size();) {
				fill(c.getRed(),c.getGreen(),c.getBlue());
				ellipse((float) withOffset.get(i).X, (float) withOffset.get(i).Y, 5, 5);
				i=i+withMidpoint/10;
			}
		}
		}
	}
	
	
	private List<Point> getPointWithOffset(float x1,float y1, float x2, float y2, float offsetPixels){
		 Double L = Math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		 double slope, angle;
		 double x1p1,x2p1,y1p1,y2p1;
		 if(x1!=x2) {
			  slope = (y2-y1)/(x2-x1);
			  	angle = Math.atan(slope);
			  	} else {
			  		angle = Math.PI/2;
			  	}
		 if(Math.toDegrees(angle)>Math.toDegrees(90)) {
		 // This is the first parallel line
		 x1p1 = x1 + offsetPixels * (y2-y1) / L.floatValue();
		 x2p1 = x2 + offsetPixels * (y2-y1) / L.floatValue();
		 y1p1 = y1 + offsetPixels * (x1-x2) / L.floatValue();
		 y2p1 = y2 + offsetPixels * (x1-x2) / L.floatValue();
		 } else {
		 // This is the second parallel line
		 x1p1 = x1 + offsetPixels * -1 * (y2-y1) / L.floatValue();
		 x2p1 = x2 + offsetPixels * -1 * (y2-y1) / L.floatValue();
		 y1p1 = y1 + offsetPixels * -1 * (x1-x2) / L.floatValue();
		 y2p1 = y2 + offsetPixels * -1 * (x1-x2) / L.floatValue();
		 }
		 Point p1 = new Point(x1p1,y1p1);
		 Point p2 = new Point(x2p1,y2p1);
		List<Point> gp = GetPoints(p1, p2);
		return gp;
	}
	
	private void drawFilters() {
		
		l.setPosition(width-200,90)
        .setSize(195, 80)
        .setItemHeight(20)
        .setBarHeight(20)
        .setColorBackground(color(0))
        //.setColorActive(0xffff9900)
        .setColorForeground(color(78));
		
		  l.getCaptionLabel().toUpperCase(true);
		  l.getCaptionLabel().set("Display Nodes By");
		  l.getCaptionLabel().setColor(255);
		  l.clear();
		  
	    l.addItem("Safety",0);
	    l.getItem(0).put("color", new CColor().setBackground(0xff888888).setBackground(0xff888888));
	    l.addItem("Node ID",1);
	    l.getItem(1).put("color", new CColor().setBackground(0xff888888).setBackground(0xff888888));
	    l.addItem("Capacity",2);
	    l.getItem(2).put("color", new CColor().setBackground(0xff888888).setBackground(0xff888888));
	    
	    l.getItem(cnt).put("color", new CColor().setBackground(0xff0066ff).setBackground(0xff0066ff));
	    cp5.draw();
	}
	
private void drawEdgeFilters() {
		
		l1.setPosition(width-200,200)
        .setSize(195, 60)
        .setItemHeight(20)
        .setBarHeight(20)
        .setColorBackground(color(0))
        .setColorForeground(color(78));
		
		  l1.getCaptionLabel().toUpperCase(true);
		  l1.getCaptionLabel().set("Display Edges By");
		  l1.getCaptionLabel().setColor(255);
		  l1.clear();
		  
	    l1.addItem("Probability",0);
	    l1.getItem(0).put("color", new CColor().setBackground(0xff888888).setBackground(0xff888888));
	    l1.addItem("Agent Capacity",1);
	    l1.getItem(1).put("color", new CColor().setBackground(0xff888888).setBackground(0xff888888));  
	    l1.getItem(cnt1).put("color", new CColor().setBackground(0xff0066ff).setBackground(0xff0066ff));
	    cp5.draw();
	}

	public void controlEvent(ControlEvent e) {
		if (e.getName() == "nodeFilters") {
			
			cnt = (int)e.getValue();
		      
		} 
		if(e.getName()=="edgeFilters") {
			
			cnt1 = (int)e.getValue(); 
		}
		
		if(e.getName()=="SaveFile") {
			l.setVisible(false);
			cp5.setVisible(false);
			bool=false;

		}
		      
	}
	
	
public List<Point> GetPoints(Point p1, Point p2) {
	  double y;
	  
   
    double j;
    List<Point> points = new ArrayList<Point>();
    if(p1.X == p2.X) {
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
    }else if(p1.X < p2.X) {
    	double slope = (p2.Y-p1.Y)/(p2.X-p1.X);
    	 double intercept = p1.Y - (slope*p1.X);
  	  for(j=p1.X;j<=p2.X;) {
  		  
  		  y = slope*j + intercept;
  		  //j=j+(p2.X-p1.X)/10;
  		  Point p = new Point(j, y);
            points.add(p);
            j=j+1;
  	  }
    } else {
    	double slope = (p2.Y-p1.Y)/(p2.X-p1.X);
    	 double intercept = p1.Y - (slope*p1.X);
  	  for(j=p1.X;j>=p2.X;) {
  		  
  		  y = slope*j + intercept;
  		  //j=j+(p1.X-p2.X)/10;
  		  Point p = new Point(j, y);
            points.add(p);
            j=j-1;
  	  }
    }
    return points;
} 

	private void fitAllIn(){
	
		
		//Panning to the center
		Point oCentroid = getCentroid();

		translate((float) (-oCentroid.X+(screenwidth/2)),(float) (-oCentroid.Y+(screenheight/2)));
	
		float maxExtentsWidth = 0 ;
		float maxExtentsHeight = 0 ;
		
		for(Node oNode:this.myPlot.lstNodes.values()) {
			if(Math.abs((oNode.longitude-oCentroid.X))>maxExtentsWidth) {
				maxExtentsWidth=(float) Math.abs(oNode.longitude-oCentroid.X);
			}
			if(Math.abs((oNode.latitude-oCentroid.Y))>maxExtentsHeight) {
				maxExtentsHeight=(float) Math.abs(oNode.latitude-oCentroid.Y);
			}
		}
		double zoomfactorX = (screenwidth/2)/maxExtentsWidth;
		double zoomfactorY=(screenheight/2)/maxExtentsHeight;
		
		if (zoomer.getZoomScale() == 1.0) {

			if(zoomfactorX<zoomfactorY) {
				zoomer.setMaxZoomScale(zoomfactorX/1.5);

			} else {
				zoomer.setMaxZoomScale(zoomfactorY/1.5);
			}
		}
		else
		{
			zoomer.setMaxZoomScale(3);
		}
		
		
		if(zoomfactorX<zoomfactorY) {
			zoomer.setMinZoomScale(zoomfactorX/2);
		} else {
			zoomer.setMinZoomScale(zoomfactorY/2);
		}
		
	}
	private Point getFourthPoint(Point P1,Point P2) {
		List<Point> allPath = new ArrayList<Point>();
		allPath = GetPoints(P1, P2);  
		if(allPath.size()>0) {
			   return allPath.get(allPath.size()/4);
			   } else {
				   return new Point(P1.X,P1.Y);
			   }
	}
	private Point getThreeFourthPoint(Point P1,Point P2) {
		List<Point> allPath = new ArrayList<Point>();
		allPath = GetPoints(P1, P2);  
		if(allPath.size()>0) {
			   return allPath.get(3*allPath.size()/4);
			   } else {
				   return new Point(P1.X,P1.Y);
			   }
	}
	private void drawRoad(float x1,float y1, float x2, float y2, int weight, Color c) {
		Double L = Math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		 float offsetPixels = roadWidth*5;
		 // This is the first parallel line
		 
		 float x1p1 = x1 + offsetPixels * (y2-y1) / L.floatValue();
		 float x2p1 = x2 + offsetPixels * (y2-y1) / L.floatValue();
		 float y1p1 = y1 + offsetPixels * (x1-x2) / L.floatValue();
		 float y2p1 = y2 + offsetPixels * (x1-x2) / L.floatValue();
		 Point P1 = new Point(x1p1,y1p1);
		 Point P2 = new Point(x2p1,y2p1);
		 
		 Point P3 = getFourthPoint(P1, P2);
		 Point P4 = getThreeFourthPoint(P1, P2);
		 
		 	//noFill();
			 noFill();
			 stroke(c.getRed(),c.getGreen(),c.getBlue());
			 
			 strokeWeight(weight); 
			 curve( (float)P4.X, (float)P4.Y,x1, y1, x2, y2,(float)P3.X, (float)P3.Y); 
			 strokeWeight(1);
		 
		}

	public Point getCentroid(){
		
		float sumX = 0;
		float sumY = 0;
		
		for(Node oNode:this.myPlot.lstNodes.values()) {
			sumX = sumX+oNode.longitude;
			sumY = sumY+oNode.latitude;
		}
		Point oPoint = new Point(sumX/this.myPlot.lstNodes.size(), sumY/this.myPlot.lstNodes.size());
		return oPoint;
		
	}
	public List<String> readFile(String path) {
		List<String> records = new ArrayList<String>();
		try {
			BufferedReader buffreader = new BufferedReader(new FileReader(path));
			String line;
			while((line=buffreader.readLine())!=null) {
				records.add(line);
			}
			buffreader.close();
			return records;
		} catch (Exception e) {
			System.err.format("Exception occurred trying to read '%s'.", path);
			e.printStackTrace();
			return null;
		}
	}
	
	private Map<Integer,Node> readNodes(List<String> records) {
		try {
			Map<Integer,Node> nodes = new HashMap<Integer,Node>();
			for(String line: records) {
				if(line.startsWith("n")) {
					String[] nodeItems = line.split("\\s");
					//nodeItems[0] = nodeItems[0].replace("NODE: ", "");
					int nodeID = Integer.parseInt(nodeItems[1].trim());
					int capacity = Integer.parseInt(nodeItems[2].trim());
					double safety = Double.parseDouble(nodeItems[3].trim());
					//double waittime = Double.parseDouble(nodeItems[2].trim());
					float longitude = Float.valueOf(nodeItems[4].trim());
					float latitude = Float.valueOf(nodeItems[5].trim());
					Node objnode = new Node(nodeID,capacity,safety,longitude,latitude,scale);
					nodes.put(nodeID,objnode);
				}
			}
			return nodes;
		} catch (Exception e) {
			System.err.format("Exception occurred trying to read nodes");
			e.printStackTrace();
			return null;
		}
	}
	private Map<Integer,Edge> readEdges(List<String> records) {
		try {
			Map<Integer,Edge> edges = new HashMap<Integer,Edge>();
			for(String line: records) {
				if(line.startsWith("e")) {
					String[] edgeItems = line.split("\\s");
					//edgeItems[0]=edgeItems[0].replace("e ", "");
					int edgeID = Integer.parseInt(edgeItems[1].trim());
					int fromID = Integer.parseInt(edgeItems[2].trim());
					int toID = Integer.parseInt(edgeItems[3].trim());
					double safety = Double.parseDouble(edgeItems[4].trim());
					Node fromNode = lstNodes.get(fromID);
					Node toNode = lstNodes.get(toID);
					double probability = lstProb.get(edgeID);
					Edge objedge = new Edge(edgeID,fromNode,toNode,safety,probability);
					edges.put(edgeID,objedge);
				}
			}
			return edges;
		} catch (Exception e) {
			System.err.format("Exception occurred trying to read edges");
			e.printStackTrace();
			return null;
		}
	}
	private void readProb(List<String> records) {
		try {
			lstProb = new HashMap<Integer,Double>();
			for(String line:records) {
				if(line.startsWith("p")) {
					String[] probItems =line.split("\\s");
					//probItems[0]=probItems[0].replace("PROB: ", "");
					int edgeID =Integer.parseInt(probItems[1].trim());
					double probability = Double.parseDouble(probItems[2].trim());
					if (lstProb.get(edgeID) == null)
					{
						lstProb.put(edgeID, probability);
					}
				}
			}
				
			
		} catch (Exception e) {
			System.err.format("Exception occurred trying to read probs");
			e.printStackTrace();
		} 
	}
	private void readAgt(List<String> records) {
		List<Node> path=new ArrayList<Node>();
		try {
			lstAgt = new HashMap<Integer,Agent>();
			for(String line:records) {
				if(line.startsWith("a")) {
					String[] agtItems = line.split("\\s");
					//agtItems[0]=agtItems[0].replace("AGNT: ", "");
					int agtID = Integer.parseInt(agtItems[1].trim());
					int i;
					
					for(i=2;i<agtItems.length;i++) {
						int nodeId = Integer.parseInt(agtItems[i].trim());
						if (lstNodes.containsKey(nodeId))
						{
							path.add(lstNodes.get(nodeId));
						}
						
					}
					Agent objagents = new Agent(agtID,path);
					lstAgt.put(agtID, objagents);
					
				}
			}
		} catch (Exception e) {
			System.err.format("Exception occurred trying to read agents");
			e.printStackTrace();
		}

	} 

}
