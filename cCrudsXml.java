// Cruds using xml

import javax.xml.parsers.*;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.Transformer;
import javax.xml.transform.Result;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

class cCrudsXml implements iCruds {

	String dataFile = "Item.xml";
	ArrayList<String> fieldNames;
	Document document;
	Element root;

	cCrudsXml() {

		try {

			DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
	        DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
	        document = docBuilder.parse(new File(dataFile));
	        root = document.getDocumentElement();
	        loadFieldNames();
		}
		catch (Exception error) {

			printErrorMessage(error);
			
		}
	}

	void loadFieldNames() {

		fieldNames = new ArrayList<>();

		fieldNames.add("ItemId");
		fieldNames.add("Description");
		fieldNames.add("UnitPrice");
		fieldNames.add("SupplierId");
		fieldNames.add("StockQty");
	}

	void printErrorMessage(Exception pError) {

		System.out.println("Error: " + pError);
	}

	public void create(ArrayList<String> pRecord) {

		// System.out.println("create");
		System.out.println(pRecord.get(0));

		Element newRecord = document.createElement("Item");

		for (int index = 0; index < fieldNames.size(); index++) {

			Element field = document.createElement(fieldNames.get(index));
			field.appendChild(document.createTextNode(pRecord.get(index)));
			newRecord.appendChild(field);
		}

		root.appendChild(newRecord);
		saveRecords();
	}

	void saveRecords() {

		try {

			DOMSource source = new DOMSource(root);
	        TransformerFactory transformerFactory = TransformerFactory.newInstance();
	        Transformer transformer = transformerFactory.newTransformer();
	        Result result = new StreamResult(new File(dataFile));
	        transformer.transform(source, result);
		}
		catch (Exception error) {
			
			printErrorMessage(error);
		}
	}

	public ArrayList<List<String>> getAllRecords() {

		ArrayList<List<String>> allRecords = new ArrayList<>();

		NodeList records = root.getElementsByTagName("Item");

		for (int recordCounter = 0; recordCounter < records.getLength(); recordCounter++) {

			List<String> newRecord = new ArrayList<>();

			Node recordData = records.item(recordCounter);
			Element pRecord = (Element) recordData;

			for (int index = 0; index < fieldNames.size(); index++) {

				NodeList fieldList = pRecord.getElementsByTagName(fieldNames.get(index));
				Element field = (Element) fieldList.item(0);
				// System.out.println(field.getTextContent());
				newRecord.add(field.getTextContent());
			}

			allRecords.add(newRecord);
		}

		return allRecords;
	}

	public ArrayList<String> getFieldNames() {

		return fieldNames;
	}
}