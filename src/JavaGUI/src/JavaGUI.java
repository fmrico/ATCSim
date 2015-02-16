import java.util.Iterator;
import java.util.List;

import ATCDisplay.ATCDFlight;


public class JavaGUI {

	private static Ice.Communicator ic = null;
	private static ATCDisplay.AirportInterfacePrx airportI = null;
	
	public static void main(String[] args) {
		int status = 0;

		try {
			String[] args1 = {new String("")};
			ic = Ice.Util.initialize(args1);
			Ice.ObjectPrx base = null;		
			
			
			base = ic.stringToProxy("AirportInterface:default -p 10000");

			airportI = ATCDisplay.AirportInterfacePrxHelper.checkedCast(base);

			while(true)
			{
				List<ATCDFlight> flights = airportI.getFlights();
				Iterator<ATCDFlight> itf = flights.iterator();
				while(itf.hasNext()){
					System.out.println("Vuelo: "+itf.next().id);
				}
				
				System.out.println("=============================");
			
				Thread.sleep(1000);
			}
		} catch (Ice.LocalException e1) {
			e1.printStackTrace();
			status = 1;
		} catch (Exception e1) {
			System.err.println(e1.getMessage());
			status = 1;
		}


	}

}
