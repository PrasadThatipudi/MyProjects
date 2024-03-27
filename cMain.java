// Main class for iCruds interface

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Scanner;

class cMain {

	private static Scanner scanner = new Scanner(System.in);
	// private static String className;

	public static void main(String[] args) {
		
		String menuFile = "Menu.cfg";
		String crudsClassNameFile = "crudsClassName.cfg";

		try {

			// loadClassName(crudsClassNameFile);
			// System.out.println("*" + getClassName(crudsClassNameFile) + "*");
			iCruds oCruds = (iCruds) Class.forName(getClassName(crudsClassNameFile)).newInstance();

			cUI oUI = new cUI(oCruds.getFieldNames());

			while (true) {

				showMenu(getMenu(menuFile), oCruds, oUI);
			}

		}

		catch (Exception error) {

			System.out.println("Main Error: " + error);
			System.exit(0);
		}
	}

	static void showMenu(String pMenu, iCruds pOCruds, cUI pOUI) {

		System.out.println(pMenu);
		System.out.print("Enter your choice here: ");

		int choice = scanner.nextInt();

		switch (choice)
		{
			case 1: pOCruds.create(pOUI.getRecord());
				break;

			case 2: pOUI.showRecords(pOCruds.getAllRecords());
				break;
				
			// case 3: pOCruds.update();
			// 	break;
				
			// case 4: pOCruds.delete();
			// 	break;
				
			// case 5: pOCruds.search();
			// 	break;
				
			// case 6: pOCruds.sort();
			// 	break;

			default: System.out.println("Invalid choice!");
				break;
				
			case 0: System.exit(0);
		}
	}

	static String getMenu(String pMenuFile) {

		String menu = "";

		try (BufferedReader brMenu = new BufferedReader(new FileReader(pMenuFile))) {

			String menuLine;

			while ((menuLine = brMenu.readLine()) != null) {

				menu += menuLine + "\n"; 
			}
		}

		catch (Exception error) {

			System.out.println("Error: " + error);
		}

		return menu;
	}

	static String getClassName(String pClassNameFile) {

		try (BufferedReader brClassName = new BufferedReader(new FileReader(pClassNameFile))) {

			String className = brClassName.readLine().trim();

			// System.out.println(className);
			return className;
		} 

		catch (Exception error) {

			System.out.println("Error: " + error);	
			return null;		
		}
	}

	
}