
	//The content of this file defines a Java class named 'ThreadBot' 
	//This class inherits from the predefined Java class Thread.

	public class ThreadBots extends Thread
	{

		int Identifier; // Identifier will identify the thread
	    char first_char;//first_char is used as the first letter in the password


		//Redefining the default constructor for this class.
		//It originally has no arguments, but we want to use
		//two arguments
		public ThreadBots(int id, char c) 
		{
			//Stores the value of the identity passed by the main class
			Identifier = id;
			//Stores the value of the character passed by the main class
			first_char = c;
		}
		
		public void run()
		{

			String currentPassword = "";
			char[] alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
			loop:
			for (int i = 0; i < alphabet.length; i++) {
				for (int j = 0; j < alphabet.length; j++) {
					for (int k = 0; k < alphabet.length; k++) {
						for (int l = 0; l < alphabet.length; l++){
							if (ThreadAttacker.found) {
								break loop;
							}
							
							currentPassword = new String(new char[] {first_char, alphabet[i], alphabet[j], alphabet[k], alphabet[l]}) + ThreadAttacker.challenge;
							if (currentPassword.hashCode() == ThreadAttacker.captured){
								System.out.println("Thread " + this.Identifier + " cracked the password: " + currentPassword +"\n");
								ThreadAttacker.found = true;
								break loop;
							}
						}
					}
				}
			}			
		}
	}



