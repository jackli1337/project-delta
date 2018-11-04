package ubhacking2018;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class driver {

	static ArrayList<String> allLines = new ArrayList<String>();
	static ArrayList<Integer> whichLines = new ArrayList<Integer>();
	static ArrayList<String> specificTitles = new ArrayList<String>();
	
	/**
	 * 
	 * @param filename
	 * the string representing the name of the file that we want to read from
	 * 
	 * reads from a CSV file and adds each line of the file as an element in an ArrayList
	 */
	public static void readTheFile(String filename) {
		File file = new File(filename);
		Scanner inputReader;
		try {
			inputReader = new Scanner(file);
			while(inputReader.hasNext()) {
				String line = inputReader.nextLine();
				allLines.add(line);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
	}
	
	/**
	 * 
	 * @param stringToDivide
	 * string containing all of the lines that the user wants transferred to the .txt file
	 * 
	 * takes the input string from the user containing the line numbers that they want transferred to the .txt file 
	 * and breaks that string down into individual lines or a range of lines that will later be 
	 * converted to ints
	 * 
	 * @return
	 * returns a vector containing either a range of lines or a single line number as element of an array
	 */
	public static String[] divideString(String stringToDivide){
		String[] splitString = stringToDivide.split(",");
		return splitString;
	}
	
	/**
	 * 
	 * @param stringArray
	 * an array of strings created by divideString containing all the lines the user wants 
	 * transferred to the .txt file (as strings)
	 * 
	 * converts all of the line numbers that the users wants transferred to ints and adds them to the 
	 * vector containing all of the lines (as ints) that the user wants transferred
	 * 
	 * all ranges have been interpreted to individual lines i.e. 1-4 = 1,2,3,4
	 */
	public static void divideEachSubString(String[] stringArray) {
		for(String s:stringArray) {
			if(s.indexOf('-')!=-1) {
				String[] numsFromDashSepString = s.split("-");
				for(int i=Integer.parseInt(numsFromDashSepString[0]);i<=Integer.parseInt(numsFromDashSepString[1]);i++) {
					whichLines.add(i);
				}
			}
			else {
				whichLines.add(Integer.parseInt(s));
			}
		}
	}
	
	/**
	 * 
	 * @param filename
	 * string of the file that we are writing out to 
	 * 
	 * writes out all of the lines that the user has requested to the output file specified
	 */
	public static void writeToTheFile(String filename) {
		try {
			FileWriter fw = new FileWriter(filename);
			for(int i=0;i<whichLines.size();i++) {
				String toWrite = allLines.get(whichLines.get(i));
				fw.write(toWrite);
				fw.write("\n");
			}
			fw.close();
		}
		catch(IOException ioe) {
			ioe.printStackTrace();
		}
	}
	
	/**
	 * this format will get all of the lines in the file that have the title info that we want 
	 * and put them in a desired format to write them to a file 
	 * 
	 * (this function is meant be be overrode to custom default formats)
	 */
	public static void formattingWriteToFile(String filename) {
		ArrayList<String> onlyTitles = new ArrayList<String>();
		onlyTitles.add(allLines.get(1));
		onlyTitles.add(allLines.get(7));
		onlyTitles.add(allLines.get(13));
		onlyTitles.add(allLines.get(19));
		onlyTitles.add(allLines.get(26));
		//test
		for(String titleLine :onlyTitles) {
			String[] splitByCommas = titleLine.split(",");
			ArrayList<String> copy = new ArrayList<String>();
			for(int i=0;i<splitByCommas.length;i++) {
				copy.add(splitByCommas[i]);
			}
			copy.remove(0);
			for(int j=0;j<copy.size();j++) {
				specificTitles.add(copy.get(j));
			}
		}

		try {
			FileWriter fw = new FileWriter(filename);
			for(int i=0;i<specificTitles.size();i++) {
				String toWrite = specificTitles.get(i);
				fw.write(toWrite + " - ");
				fw.write("\n");
				fw.write("Cutline: " + "\n" + " " + "\n");
				fw.write("\n");
			}
			fw.close();
		}
		catch(IOException ioe) {
			ioe.printStackTrace();
		}
	}
	
	public static void main(String[]args) {
		Scanner keyboard1 = new Scanner(System.in);
		System.out.println("Choose One:Default Format(true) OR Manually Select Lines(false)");
		boolean choice = keyboard1.nextBoolean();
		
		if(choice) {
			readTheFile("/Users/Tim/Downloads/data.csv");
			formattingWriteToFile("/Users/Tim/Desktop/output.txt");
		}
		if(!choice){
			Scanner keyboard2 = new Scanner(System.in);
			System.out.println("Enter what lines from the file you want (first line is #0): ");
			String inputString= keyboard2.nextLine();	

			String[] dividedString = divideString(inputString);
			divideEachSubString(dividedString);		
			
			readTheFile("/Users/Tim/Downloads/data.csv");
			writeToTheFile("/Users/Tim/Desktop/output.txt");
			
		}
	}
}