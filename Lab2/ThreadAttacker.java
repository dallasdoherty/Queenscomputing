
	
public class ThreadAttacker {

		//This is the challenge value, you can modify the value if you want
		public static String challenge = " challenge_sequence ";
		//This is the password. It is here to help us compute the correct response that corresponds to the challenge
		public static String password = "virus"; 
		//This is the variable that represents the captured response
		public static int captured;
		//This is the variable that will be used by the thread to inform each other that the password has been cracked
		//For instance, if a thread cracks the password, it update the value of this variable to true
		public static volatile boolean found = false;

		//The main method, here starts the execution	
		public static void main(String[] args) throws InterruptedException 
		{
			char[] firstOrder = {'i', 't', 'v'};
			char[] secondOrder = {'i', 'v', 't'};
			
			//tempx is a temporary string variable that we are using to create the concatenation of the password with the challenge 
			String tempx = password + challenge;
			
			//Here we create the response by computing the hash of the previously computed string object
			captured = tempx.hashCode();
			
			//Create the three threads
			ThreadBots t_1 = new ThreadBots(1, 'i');
			ThreadBots t_2 = new ThreadBots(2, 't');
			ThreadBots t_3 = new ThreadBots(3, 'v');
					
			//Thread triggering (starting the threads)
			//counting time
			long startTime = System.nanoTime();
			
			t_1.start();
			t_2.start();
			t_3.start();
			try {
				t_1.join();
				t_2.join();
				t_3.join();
			} 
			catch (InterruptedException e) {
				e.printStackTrace();
			}
			
			long amountOfTime = (System.nanoTime() - startTime)/1000000;
			System.out.println("Threaded time in miliseconds:" + amountOfTime + "\n");

			startTime = System.nanoTime();
			String curr = nonThreaded(firstOrder);
			amountOfTime = (System.nanoTime() - startTime)/1000000;
			System.out.println("Non Threaded, order i, t, v time in miliseconds: " + amountOfTime + "\nPassword: " + curr + "\n");
			
			startTime = System.nanoTime();
			curr = nonThreaded(secondOrder);
			amountOfTime = (System.nanoTime() - startTime)/1000000;
			System.out.println("Non Threaded, order i, v, t time in miliseconds: " + amountOfTime + "\nPassword: " + curr + "\n");

		}

		public static String nonThreaded(char[] firstLetter){
			
			char[] alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
			for (int i = 0; i < firstLetter.length; i++){
				for (int j = 0; j < alphabet.length; j++){
					for (int k = 0; k < alphabet.length; k++) {
						for (int l = 0; l < alphabet.length; l++) {
							for (int m = 0; m < alphabet.length; m++){
								if ((new String(new char[] {firstLetter[i], alphabet[j], alphabet[k], alphabet[l], alphabet[m]}) + challenge).hashCode() == captured) {
									return (new String(new char[] {firstLetter[i], alphabet[j], alphabet[k], alphabet[l], alphabet[m]}) + challenge);
								}
							}
						}
					}
				}
			}
			return ("Not Found");
		}

	}


