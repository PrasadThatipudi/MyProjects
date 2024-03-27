// Cruds using sqlite

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

class cCrudsSqlite implements iCruds {

	private Connection connection = null;
	private Statement statement = null;
	private PreparedStatement updateStatement;
	private String table = "Item", query;
	private ArrayList<String> fieldNames;

	cCrudsSqlite() {

		try {

			String database = "dbPrasad.db";
			connection = DriverManager.getConnection("jdbc:sqlite:D:\\Training\\JavaPrograms\\" + database);

			if (connection != null) {

				statement = connection.createStatement();
				System.out.println("You successfully connected with database '" + database + "'.");

				loadFieldNames();

				// System.out.println(fieldNames);
			}
		}
		catch (Exception error) {
			
			printErrorMessage(error);
		}
	}

	void printErrorMessage(Exception pError) {

		System.out.println("Error: " + pError);
	}

	public void create(ArrayList<String> pRecord) {

		query = "insert into " + table + " values(?";

		for (int index = 1; index < fieldNames.size(); index++) {

			query += ", ?";
		}
		
		query += ");";

		try {

			updateStatement = connection.prepareStatement(query);

			for (int index = 0; index < fieldNames.size(); index++) {

				updateStatement.setString((index + 1), pRecord.get(index));
			}

			executeUpdateQuery(pRecord.get(0), "inserted");
		}
		catch (Exception error) {

			printErrorMessage(error);
		}

	}

	void executeUpdateQuery(String pRecordId, String processNameInV2Form) {

		if (getNumberOfRowsAffected() > 0) {

			System.out.println(fieldNames.get(0) + " '" + pRecordId + "' " + processNameInV2Form + " successfully.");
		}
		else {

			System.out.println("Error occured during the process.");
		}
	}

	int getNumberOfRowsAffected() {

		int numberOfRowsAffected = 0;

		try {

			numberOfRowsAffected = updateStatement.executeUpdate();
		}
		catch (Exception error) {
			
			printErrorMessage(error);
		}

		return numberOfRowsAffected;
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

	public ResultSet getResultSetOfAllRecords() {

		try {

			ResultSet resultSetOfRecords = statement.executeQuery("select * from " + table);
			return resultSetOfRecords;
		}
		catch (Exception error) {

			printErrorMessage(error);
			return null;
		}

	}

	public ArrayList<String> getFieldNames() {

		return fieldNames;
	}

	public void loadFieldNames() {

		fieldNames = new ArrayList<>();

		try {

			DatabaseMetaData metaData = connection.getMetaData();
			ResultSet columnNamesResultSet = metaData.getColumns(null, null, table, null);

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
}