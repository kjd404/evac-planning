import processing.core.PApplet;
import processing.core.PConstants;
public class callOut {
	private Node oNode;
	private float roadWidth;
	PApplet parent;
	public callOut(Node coNode,float croadWidth,PApplet p){
		oNode =coNode;
		roadWidth=croadWidth;
		parent = p;
	}
	public void display() {
		float nodeRadius = roadWidth/4; //roundAboutWidth is half of roadWidth; hence radius is 1/4th
		float x1 = oNode.longitude;
		float y1 = oNode.latitude-nodeRadius;
		float x2 = x1 - nodeRadius;
		float y2 = y1 - nodeRadius;
		float x3 = x1 + nodeRadius;
		float y3 = y1 - nodeRadius;
		//parent.pushMatrix();
		parent.fill(51,255,51);
		//parent.noStroke();
		parent.triangle(x1, y1, x2, y2, x3, y3);
		float x11 = x1 - (3*nodeRadius);
		float y11 = y2+(nodeRadius/100);
		float x22 = x1 + (3*nodeRadius);
		float y22 = y11;
		float x33 = x22;
		float y33 = y2 - (3*nodeRadius);
		float x44 = x11;
		float y44 = y33;
		parent.quad(x11, y11, x22, y22, x33, y33, x44, y44);
		parent.fill(0);
		parent.textFont(parent.createFont("serif Bold",(float) (0.6*nodeRadius)));
	    parent.textAlign(PConstants.TOP,PConstants.LEFT);
		String nodeText ="Safety" +String.format(15-"Safety".length() +"s", " ") + ":" + oNode.safety +"\n";
		nodeText = nodeText + "Capacity"+String.format(15-"Capacity".length() +"s", " ") + ":" + oNode.capacity + "\n";
		//nodeText = nodeText + "Wait Time"+String.format(15-"Wait Time".length() +"s", " ") + ":" +oNode.waitTime;
		parent.text(nodeText,x11 +(nodeRadius/10), (float) (y33+(nodeRadius/1.5)) );
		//parent.popMatrix();
	}
}
