import java.io.File;

public class PlotProperties {
	String filename;
	nodeColumn nColumn = nodeColumn.Safety; 
	edgeColumn eColumn = edgeColumn.Safety;
	nodeShape nShape = nodeShape.Circle;
	edgeSize eSize = edgeSize.Probability;
	nodeLabel nLabel = nodeLabel.Safety;
	enum nodeColumn {
		Safety, Capacity;
	}
	enum edgeColumn {
		Safety, Capacity;
	}
	double eMin,eMax;
	double	nMin, nMax;
	Color nMinColor = Color.Red;
	Color nMaxColor = Color.Blue;
	Color eMinColor = Color.Black;
	Color eMaxColor = Color.Black;
	enum nodeShape {
		Circle, Triangle, Square;
	}
	enum edgeSize {
		Probability, Capacity;
	}
	enum nodeLabel {
		Safety, nodeID,Capacity;
	}
	double eShapeVal=0.02;
	boolean propertyError=false;
	double nSizeVal=1.0;
	
	public PlotProperties(String[] args) {
		if(GetFilePath(args)==false) {
			propertyError = true;
			return;
		}
		if(GetNodeColumn(args)==false) {
			propertyError=true;
		} else {
			if(GetNodeValue(args)==false) {
				propertyError=true;
			} else if(GetNodeColor(args)==false) {
				propertyError = true;
			}
		}
		if(GetEdgeColumn(args)==false) {
			propertyError=true;
		} else {
			if(GetEdgeValue(args)==false) {
				propertyError=true;
			} else if(GetEdgeColor(args)==false) {
				propertyError = true;
			}
		}
		if(GetNodeShape(args)==false) {
			propertyError=true;
		}
		if(GetEdgeShape(args)==false) {
			propertyError=true;
		}
		if(GetNodeSize(args)==false) {
			propertyError=true;
		}
		if(GetEdgeSize(args)==false) {
			propertyError=true;
		}
		if(GetNodeLabel(args)==false) {
			propertyError=true;
		}
	}
	private boolean GetFilePath(String[] args) {
		for(int i=0;i<args.length;i++) {
			if(args[i].equals("-f")) {
				if((i+1)<args.length) {
						File sampleFile = new File(args[i+1]);
						boolean exists = sampleFile.exists();
						if (!exists) {
							sampleFile =  new File(System.getProperty("user.dir") + "/" + args[i+1]);
						}
						exists = sampleFile.exists();
						if(exists)
						{
							filename=sampleFile.getPath();
							return true;
						
						} else {
							System.out.println("Input File doesn't exist");
							return false;
						}
					} else {
						System.out.println("Please specify filename");
						return false;
					}
			}
		}
	return false;
}
	
	private boolean GetNodeColumn(String[] args) {
		for(int i=0;i<args.length;i++) {
			if(args[i].equals("-ncolor")) {
				if((i+1)<args.length) {
					if(args[i+1].equals("0")) {
						nColumn=nodeColumn.Safety;
						return true;
					} else if(args[i+1].equals("1")) {
						nColumn = nodeColumn.Capacity;
						return true;
					} else {
						System.out.println("ncolor accepts first argument for column number as either 0 for safety or 1 for capacity");
						return false;
					}
				} else {
					System.out.println("ncolor accepts <node column number{0:Safety[default], 1:Capacity}> <nmin:nmax{default[0:1]}> <nminColor:nmaxColor{default[red:blue]}> \n");
					return false;
				}
			}
		} 
		return true;
		
	}
	
	private boolean GetNodeValue(String[] args) {
		for(int i=0;i<args.length;i++) {
			if(args[i].equals("-ncolor")) {
				if((i+2)<args.length) {
					if(args[i+2].contains(":")) {
						String nodeVal[] = args[i+2].split(":");
						nMin = Double.parseDouble(nodeVal[0]);
						nMax = Double.parseDouble(nodeVal[1]);
						return true;
					} else {
						System.out.println("ncolor accepts second argument <nmin:nmax{default[0:1]}>");
						return false;
					}
				} else {
					System.out.println("-ncolor accepts <node column number{0:Safety[default], 1:Capacity}> <nmin:nmax{default[0:1]}> <nminColor:nmaxColor{default[red:blue]}> \n");
					return false;
				}
			}
		}
		return true;
	}
	
	private boolean GetNodeColor(String[] args) {
		for(int i=0;i<args.length;i++) {
			if(args[i].equals("-ncolor")) {
				if((i+3)<args.length) {
					if(args[i+3].contains(":")) {
						String nodeColorVal[] = args[i+3].split(":");
						try {
							
							nMinColor = Color.valueOf(nodeColorVal[0]);
							
						} catch(Exception e) {
							
							System.out.println("Color doesn't exist in list");
						}
						try {
							nMaxColor = Color.valueOf(nodeColorVal[1]);
							
						} catch(Exception e) {
							System.out.println("Color doesn't exist in list");
						}
						return true;
					} else {
						System.out.println("ncolor accepts third argument <nminColor:nmaxColor{default[red:blue]}>");
						return false;
					}
				} else {
					System.out.println("-ncolor accepts <node column number{0:Safety[default], 1:Capacity}> <nmin:nmax{default[0:1]}> <nminColor:nmaxColor{default[red:blue]}> \n");
					return false;
				}
			}
		}
		return true;
	}
	private boolean GetEdgeColumn(String[] args) {
		for(int i=0;i<args.length;i++) {
			if(args[i].equals("-ecolor")) {
				if((i+1)<args.length) {
					if(args[i+1].equals("0")) {
						eColumn=edgeColumn.Safety;
						return true;
					} else if(args[i+1].equals("1")) {
						eColumn = edgeColumn.Capacity;
						return true;
					} else {
						System.out.println("ecolor accepts first argument for column number as either 0 for safety or 1 for capacity");
						return false;
					}
				} else {
					System.out.println("ecolor <edge column number{0:Safety, 1:Capacity}> <nmin:nmax> <eminColor:emaxColor> \n");
					return false;
				}
			}
		} 
		return true;	
	}
	
	private boolean GetEdgeValue(String[] args) {
		for(int i=0;i<args.length;i++) {
			if(args[i].equals("-ecolor")) {
				if((i+2)<args.length) {
					if(args[i+2].contains(":")) {
						String colVal[] = args[i+2].split(":");
						eMin = Double.parseDouble(colVal[0]);
						eMax = Double.parseDouble(colVal[1]);
						return true;
					} else {
						System.out.println("ecolor accepts second argument <emin:emax{default[0:1]}>");
						return false;
					}
				} else {
					System.out.println("-ecolor accepts <node column number{0:Safety[default], 1:Capacity}> <nmin:nmax{default[0:1]}> <nminColor:nmaxColor{default[red:blue]}> \n");
					return false;
				}
			}
		}
		return true;
	}
	private boolean GetEdgeColor(String[] args) {
		for(int i=0;i<args.length;i++) {
			if(args[i].equals("-ecolor")) {
				if((i+3)<args.length) {
					if(args[i+3].contains(":")) {
						String [] edgeColorVal= args[i+3].split(":");
						try {
							eMinColor = Color.valueOf(edgeColorVal[0]);
						} catch(Exception e) {
							System.out.println("Color doesn't exist in list");
						}
						try {
							eMaxColor = Color.valueOf(edgeColorVal[1]);
						} catch(Exception e) {
							System.out.println("Color doesn't exist in list");
						}
						return true;
					} else {
						System.out.println("ncolor accepts third argument <nminColor:nmaxColor{default[red:blue]}>");
						return false;
					}
				} else {
					System.out.println("-ncolor accepts <node column number{0:Safety[default], 1:Capacity}> <nmin:nmax{default[0:1]}> <nminColor:nmaxColor{default[red:blue]}> \n");
					return false;
				}
			}
		}
		return true;
	}
	private boolean GetNodeShape(String[] args) {
		for(int i=0;i<args.length;i++) {
			if(args[i].equals("-nshape")) {
				if((i+1)<args.length) {
					if(args[i+1].equals("0")) {
						nShape=nodeShape.Circle;
						return true;
					} else if(args[i+1].equals("1")) {
						nShape=nodeShape.Triangle;
						return true;
					} else if(args[i+1].equals("2")) {
						nShape=nodeShape.Square;
						return true;
					} else {
						System.out.println("nshape accepts nxt argument either 0 for Circle, 1 for Triangle and 2 for Square");
						return false;
					}
				} else {
					System.out.println("nshape <Shape of the node>{0:circle, 1:triangle, 2:square}<Default:0> \n");
					return false;
				}
			}
		} 
		return true;
	}
	
	private boolean GetEdgeShape(String[] args) {
		for(int i=0;i<args.length;i++) {
			if(args[i].equals("-eshape")) {
				if((i+1)<args.length) {
					try {
						eShapeVal = Double.parseDouble(args[i+1]); 
						if(eShapeVal>=0 && eShapeVal<=1) {
							return true;
						}	
						 else {
							System.out.println("eshape accepts value between 0 and 1");
							return false;
						}
					} catch (Exception e) {
						// TODO: handle exception
						System.out.println("eshape accepts value between 0 and 1");
					}
					
				} else {
					System.out.println("-eshape <Accepts probability value, any value less than this represented as dotted line> \n");
					return false;
				}
			}
		} 
		return true;
	}
			
	private boolean GetNodeSize(String[] args) {
		for(int i=0;i<args.length;i++) {
			if(args[i].equals("-nxsize")) {
				if((i+1)<args.length) {
					nSizeVal = Double.parseDouble(args[i+1]);
					if(nSizeVal>0) {
						return true;
					} else {
						System.out.println("nsize accepts argument value greater than zero");
						return false;
					}
				} else {
					System.out.println("nsize accepts argument value greater than zero \n");
					return false;
				}
			}
		} 
		return true;
	}
	
	private boolean GetEdgeSize(String[] args) {
		for(int i=0;i<args.length;i++) {
			if(args[i].equals("-esizeOn")) {
				if((i+1)<args.length) {
					if(args[i+1].equals("0")) {
						eSize=edgeSize.Probability;
						return true;
					} else if(args[i+1].equals("1")) {
						eSize=edgeSize.Capacity;
						return true;
					} else {
						System.out.println("esize <edge column number{0:probability[default], 1:Capacity}>");
						return false;
					}
				} else {
					System.out.println("esize <edge column number{0:probability[default], 1:Capacity}>\n");
					return false;
				}
			}
		} 
		return true;
	}
	
	private boolean GetNodeLabel(String[] args) {
		for(int i=0;i<args.length;i++) {
			if(args[i].equals("-nlabel")) {
				if((i+1)<args.length) {
					if(args[i+1].equals("0")) {
						nLabel=nodeLabel.Safety;
						return true;
					} else if(args[i+1].equals("1")) {
						nLabel=nodeLabel.nodeID;
						return true;
					} else if(args[i+1].equals("2")) {
						nLabel=nodeLabel.Capacity;
						return true;
					} else {
						System.out.println("-nlabel accepts argument value 0:Safety, 1:nodeID, 2:Capacity");
						return false;
					}
				} else {
					System.out.println("-nlabel <node label{0:Safety[default], 1:nodeID, 2:Capacity}>\n");
					return false;
				}
			}
		} 
		return true;
	}
	
	
}
