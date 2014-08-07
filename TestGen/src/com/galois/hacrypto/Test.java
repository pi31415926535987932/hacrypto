package com.galois.hacrypto;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Scanner;

import javax.management.RuntimeErrorException;

import org.stringtemplate.v4.ST;



public class Test {
	
	//map from algorithm names to KATs
	private Map<String, KAT> kats = new HashMap<String, KAT>();
	//map from algorithm names to autogenerated input file names
	private Map<String, String> testFiles = new HashMap<String, String>();
	
	private List<String> languages = new LinkedList<String>();
	
	private File outDir;
	private File testDir;
	
	public Test(String testDir, String outDir){
		this.outDir = new File(outDir);
		this.testDir = new File(testDir);
		this.outDir.mkdirs();
		this.testDir.mkdirs();
		File testFile = new File(testDir + File.separator + "tests");
		Scanner testReader = null; 
		try {
			 testReader= new Scanner(testFile);
		} catch (FileNotFoundException e) {
			System.err.println("File " + testFile.getAbsolutePath() + " not found");
			e.printStackTrace();
		}
		while(testReader.hasNext()){
			readTestLine(testReader.nextLine());
		}
	}
	
	public void generateLanguageTests(){
		for(String s : languages){
			if (s.toUpperCase().equals("C")){
				CTests ct = new CTests();
				ct.writeTestFiles(outDir, testDir, this);
			}
			else{
				throw new RuntimeErrorException(new Error("Unsupported language " + s));
			}
		}
	}
	
	public KAT getKAT(String algorithm){
		return kats.get(algorithm);
	}
	
	public String getTestFile(String algorithm){
		return testFiles.get(algorithm);
	}
	
	//TODO: More extensible solution
	private String translateAlgorithm(String algorithm){
		if(algorithm.equals("SHA256")){
			return "SHA-256";
		}
		return algorithm;
	}
	
	private void readTest(Scanner testReader, String algorithm){
		String testType = testReader.next();
		
		if(testType.toUpperCase().equals("KAT")){
			KAT kat = new KAT(testDir.getPath() + File.separator + algorithm + "_KAT");
			kats.put(algorithm, kat);
		}
		else if(testType.toUpperCase().equals("COMPARE")){
			KAT kat=null;
			try {
				kat = new KAT(testReader.nextInt(), testReader.nextInt(), testReader.nextInt(), translateAlgorithm(algorithm));
			} catch (NoSuchAlgorithmException e) {
				e.printStackTrace();
			}
			
			Entry<String,String> inout = kat.simpleStrings();
			writeStringToOutDir(algorithm + "_compare_in", outDir.getPath(), inout.getKey());
			writeStringToOutDir(algorithm + "_compare_out", outDir.getPath(), inout.getValue());
			testFiles.put(algorithm, algorithm + "_compare");
		}
		
		else{
			throw new RuntimeErrorException(new Error("Unimplemented test type: " + testType));
		}
	}
	
	private void readTestLine(String line){
		Scanner lineReader = new Scanner(line);
		String algorithm = lineReader.next();
		if(algorithm.toUpperCase().equals("LANGUAGES")){
			while(lineReader.hasNext()){
				languages.add(lineReader.next());
			}
		}
		while(lineReader.hasNext()){
			readTest(lineReader, algorithm);
		}
		
	}
	
	public static void writeStringToOutDir(String filename, String outputDirectory, String toWrite){
		File outfile = new File(outputDirectory + File.separator + filename);
		try {
			outfile.createNewFile();
		} catch (IOException e) {
			System.err.println("could not create file " + outfile.getAbsolutePath());
			e.printStackTrace();
		}
	
		try {
			PrintWriter out = new PrintWriter(outfile);
			out.print(toWrite);
			out.close();
		} catch (IOException e) {
			System.err.println("Problem writing to file " + outfile.getAbsolutePath());
			e.printStackTrace();
		}
	}

	public static void writeSTToOutDir(String filename, String outputDirectory, ST toWrite){
		File outfile = new File(outputDirectory + File.separator + filename);
		
		try {
			outfile.createNewFile();
		} catch (IOException e) {
			System.err.println("could not create file " + outfile.getAbsolutePath());
			e.printStackTrace();
		}
	
		try {
			toWrite.write(outfile, null);//TODO: figure out what to do for second argument
		} catch (IOException e) {
			System.err.println("Problem writing to file " + outfile.getAbsolutePath());
			e.printStackTrace();
		}
	}
	
	public static String hexToCUChar(String st){
		StringBuilder sb = new StringBuilder();
		if(st.length() % 2 !=0){
			throw new RuntimeErrorException(null, "String " + st + " is not a valid length for a digest");
		}
		for(int i=0; i<st.length(); i=i+2){
			sb.append("0x");
			sb.append(st.charAt(i));
			sb.append(st.charAt(i+1));
			if(i+2 < st.length()){
				sb.append(", ");
			}
			if(i!=0 && (i+2)%16 == 0){
				sb.append("\n");
			}
		}
		return sb.toString();
	}
	
	public static void main(String args[]){
		new Test("test_defs", "../callsha/tests2").generateLanguageTests();
	}
	
	
}
