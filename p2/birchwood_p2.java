public class birchwood_p2 {
	// x1: 0 = L, 1 = C, 2 = R
	// x[2,4]: false = L, true = R
	public static class Configuration {
		int x1; // initially all pointed left
		boolean[] xLower = new boolean[3];  

		// this function is lame, is there any way to set a macro or something from char to int?
		public Configuration(String states) {
			// configure x1 from input
			if (states.charAt(0) == 'L') {
				x1 = 0;
			}
			else if (states.charAt(0) == 'C') {
				x1 = 1;
			}
			else {
				x1 = 2;
			}

			// configure the lower gates from input 
			for (int i = 0; i < 3; i++) {
				if (states.charAt(0) == 'L') {
					xLower[i] = false;
				}
				else {
					xLower[i] = true;
				}
			}
		}

		void printConfiguration() {
			if (x1 == 0) {
				System.out.print("L");
			}
			else if (x1 == 1) {
				System.out.print("C");
			}
			else {
				System.out.print("R");
			}

			for(int i = 0; i < 3; i++) {
				if (xLower[i]) {
					System.out.print("R");
				}
				else {
					System.out.print("L");
				}
			}
		}
		
		// This function is also kind of lame, but whatever it works
		char lowerGateOutputChute(boolean setting, int gate) {
			if (gate == 0) {
				if (!setting) {
					return 'B';
				}
				else {
					return 'C';
				}
			}
			else if (gate == 1) {
				if (!setting) {
					return 'C';
				}
				else {
					return 'D';
				}
			} 
			else {
				if (!setting) {
					return 'D';
				}
				else {
					return 'E';
				}
			}
		}
		// 0 toggles x1 to the left (subtracting), 1 toggles x1 to the right (adding)
		char dropMarble(int token) {
			char returnChar;

			returnChar = lowerGateOutputChute(xLower[x1], x1); // get output chute from current configuration

			// update configuration
			xLower[x1] = !xLower[x1]; // toggle lower gate
		
			// rotate top gate 
			x1 = (x1 + (token == 1 ? 1 : 2)) % 3;

			return returnChar;
		}
	}

	static void computeFromInput(String input, Configuration automaton) {
		
		char c = ' ';
		for(int i = 0; i < input.length(); i++) {
			automaton.printConfiguration();
			c = automaton.dropMarble(Character.getNumericValue(input.charAt(i)));
			System.out.print("->");
		}
		automaton.printConfiguration();
		System.out.println(" " + c);
	}
	public static void main(String[] args){
		Configuration M = new Configuration(args[0]);
		computeFromInput(args[1], M);
	}
}