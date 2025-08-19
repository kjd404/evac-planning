public class EvacPlanning {
	public static void main(String[] args) {
		//File sampleFile = new File("/Users/homanaren/Documents/Plot/mrccpCityFinal.txt");
		
		if (args.length ==0){
			//System.out.println("accepts arg1: filename - Abosulte or Releative path");
			System.out.println("Help menu for plotting: /n");
			System.out.println("-f <filename{Absolute or Relative path}> \n"); 
			System.out.println("-ncolor <node column number{0:Safety[default], 1:Capacity}> <nmin:nmax{default[0:1]}> <nminColor:nmaxColor{default[red:blue]}> \n");
			System.out.println("-ecolor <edge column number{0:Safety, 1:Capacity}> <emin:emax> <eminColor:emaxColor>\n");
			System.out.println("-nshape <Shape of the node>{0:circle, 1:triangle, 2:square}<Default:0> \n");
			System.out.println("-eshape <Accepts probability value, any value less than this represented as dotted line>");
			System.out.println("-nxsize xTimesOriginalSize");
			System.out.println("-esizeOn <edge column number{0:probability[default], 1:Capacity}>");
			System.out.println("-nlabel <node label{0:Safety[default], 1:nodeID, 2:Capacity}>");
			return;
		} else {
//			PlotProperties oPlotProp = new PlotProperties(args);
//			if(oPlotProp.propertyError==false) {
				NetworkXPlot objPlot = new NetworkXPlot(args);
//			}
		}
		
		
	}
}
