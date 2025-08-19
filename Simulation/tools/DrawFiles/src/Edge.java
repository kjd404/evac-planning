import java.awt.Color;

public class Edge {
	int edgeID;
	Node fromNode;
	Node toNode;
	double safety;
	double probability;
	int agtCapacity;
	public Edge(int edgeID2, Node fromNode2, Node toNode2, double safety2, double probability2) {
		edgeID=edgeID2;
		fromNode=fromNode2;
		toNode=toNode2;
		safety=safety2;
		probability=probability2;
	}
	public void addAgent() {
		agtCapacity++;
	}
	public Color getEdgeColor(PlotProperties oPlotProp) {
		Color c = null;
		if(oPlotProp.eColumn.toString().equals("Safety")) {
		if(this.safety==oPlotProp.eMin) {
			c = new Color(oPlotProp.eMinColor.getRed(),oPlotProp.eMinColor.getGreen(),oPlotProp.eMinColor.getBlue());
		}
		else if(this.safety==oPlotProp.eMax){
			c = new Color(oPlotProp.eMaxColor.getRed(),oPlotProp.eMaxColor.getGreen(),oPlotProp.eMaxColor.getBlue());
		}
		else {
			c= new Color((int) ((1-safety)*oPlotProp.eMaxColor.getRed()),oPlotProp.eMaxColor.getGreen(),(int) safety*oPlotProp.eMaxColor.getBlue());
		}
		} 
		else if(oPlotProp.eColumn.toString().equals("Capacity")) {
			if(this.agtCapacity==oPlotProp.eMin) {
				c = new Color(oPlotProp.eMinColor.getRed(),oPlotProp.eMinColor.getGreen(),oPlotProp.eMinColor.getBlue());
			}
			else if(this.agtCapacity==oPlotProp.eMax){
				c = new Color(oPlotProp.eMaxColor.getRed(),oPlotProp.eMaxColor.getGreen(),oPlotProp.eMaxColor.getBlue());
			}
			else {
				c= new Color((int) ((oPlotProp.eMinColor.getRed()+oPlotProp.eMaxColor.getRed()))/2,(oPlotProp.eMinColor.getGreen()+oPlotProp.eMaxColor.getGreen())/2,(oPlotProp.eMinColor.getBlue()+oPlotProp.eMaxColor.getBlue())/2);
			}
		}
		return c;
	}
}
