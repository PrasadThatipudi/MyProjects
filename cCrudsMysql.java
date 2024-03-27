// Cruds using mysql database

import java.sql.*;
import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;

class cCrudsMysql implements iCruds {

	private Connection connection;
	private Statement statement;
    private PreparedStatement updateStatement;
	private ArrayList<String> fieldNames;
	private String query, table = "Item";
	private Scanner scanner = new Scanner(System.in);
	private ResultSet records;
	private int maximumLengthOfName = 25;

	cCrudsMysql() {

		String host = "138.68.140.83", database = "dbPrasad", user = "Prasad", password = "Prasad@123";
		
		try {

			connection = DriverManager.getConnection("jdbc:mysql://" + host + ":3306/" + database, user, password);

			if (connection != null) {

				System.out.println("You successfully connected with database '" + database + "'.");
			}
	
			statement = connection.createStatement();

			loadFieldNames();
			// System.out.println(fieldNames);
		}

		catch (SQLException error) {

			printErrorMessage(error);
			System.exit(0);
		}
	}	

	public ArrayList<String> getFieldNames() {

		return fieldNames;
	}

	public void loadFieldNames() {

		try {

			DatabaseMetaData metaData = connection.getMetaData();
			ResultSet columnNamesResultSet = metaData.getColumns(null, null, table, null);

			fieldNames = new ArrayList<>();
			String columnName;

			while (columnNamesResultSet.next()) {

				columnName = columnNamesResultSet.getString("COLUMN_NAME");
				
				if (fieldNames.contains(columnName) == true) {

					break;
				}
				else {

					fieldNames.add(columnName);
				}
			}
		}
		catch (Exception error) {
			
			printErrorMessage(error);
		}
	}

	public ResultSet getResultSetOfAllRecords() {

		ResultSet records;

		try {

			records = statement.executeQuery("select * from " + table);
			return records;
		}
		catch (Exception error) {
			
			printErrorMessage(error);
			return null;
		}

	}
	
	public void create(ArrayList<String> pRecord) {

		// System.out.println("create");

		// System.out.println(pRecord);

		query = "insert into " + table + " values( ?";

		for (int index = 1; index < fieldNames.size(); index++) {

			query += ", ?";
		}

		query += ");";

		try {

			PreparedStatement updateStatement = connection.prepareStatement(query);

			for (int index = 0; index < fieldNames.size(); index++) {

				updateStatement.setString((index + 1), pRecord.get(index));
			}

			int rowsAffected = updateStatement.executeUpdate();

			if (rowsAffected > 0 ) {

				System.out.println(fieldNames.get(0) + " '" + pRecord.get(0) + "' inserted successfully.");
			}
			else {

				System.out.print("Error occured while inserting.");
			}
		}

		catch (Exception error) {
			
			printErrorMessage(error);
		}
	}
	
	void printErrorMessage(Exception pError) {

		System.out.println("Error: " + pError);
	}

	public ArrayList<List<String>> getAllRecords() {

		ResultSet recordsResultSet = getResultSetOfAllRecords();

		try {

			if (recordsResultSet.isBeforeFirst() == true) {

				ArrayList<List<String>> records = new ArrayList<>();

				while (recordsResultSet.next()) {
					
					List<String> newRecord = new ArrayList<>();

					for (int index = 0; index < fieldNames.size(); index++) {

						newRecord.add(recordsResultSet.getString(fieldNames.get(index)));
					}

					records.add(newRecord);
				}

				return records;
			}
			else {
				
				System.out.println("No records found!");
				return null;
			}
		}
		catch (Exception error) {
			
			printErrorMessage(error);
			return null;
		}
	}
}

