import java.awt.Color;


public class Node {
	public int ID;
	public int capacity;
	public double safety;
	//public double waitTime;
	public float longitude;
	public float latitude;
	public int filter=0;
	
	public Node(int cnodeID,int ccapacity,double csafety,float clongitude, float clatitude,float scale) {
		ID = cnodeID;
		capacity = ccapacity;
		safety = csafety;
		//waitTime = cwaittime;
		longitude = clongitude * scale;
		latitude = clatitude * scale;
	}
	public Color getNodeColor(PlotProperties oPlotProp) {
		Color c = null;
		if(oPlotProp.nColumn.toString().equals("Safety")) {
		if(this.safety==oPlotProp.nMin) {
			c = new Color(oPlotProp.nMinColor.getRed(),oPlotProp.nMinColor.getGreen(),oPlotProp.nMinColor.getBlue());
		}
		else if(this.safety==oPlotProp.nMax){
			c = new Color(oPlotProp.nMaxColor.getRed(),oPlotProp.nMaxColor.getGreen(),oPlotProp.nMaxColor.getBlue());
		}
		else {
			c= new Color((int) ((1-safety)*oPlotProp.nMaxColor.getRed()),oPlotProp.nMaxColor.getGreen(),(int) safety*oPlotProp.nMaxColor.getBlue());
		}
		} 
		else if(oPlotProp.nColumn.toString().equals("Capacity")) {
			filter=2;
			if(this.capacity==oPlotProp.nMin) {
				c = new Color(oPlotProp.nMinColor.getRed(),oPlotProp.nMinColor.getGreen(),oPlotProp.nMinColor.getBlue());
			}
			else if(this.capacity==oPlotProp.nMax){
				c = new Color(oPlotProp.nMaxColor.getRed(),oPlotProp.nMaxColor.getGreen(),oPlotProp.nMaxColor.getBlue());
			}
			else {
				c= new Color((int) ((oPlotProp.nMinColor.getRed()+oPlotProp.nMaxColor.getRed()))/2,(oPlotProp.nMinColor.getGreen()+oPlotProp.nMaxColor.getGreen())/2,(oPlotProp.nMinColor.getBlue()+oPlotProp.nMaxColor.getBlue())/2);
			}
		}
		return c;
	}
	public String getNodeByFilter(int filter) {
		switch(filter) {
		case 0:
			return Double.toString(safety);
		case 1:
			return Integer.toString(ID);
		case 2:
			return Integer.toString(capacity);
		
		}
		return null;
		 
	}
}
