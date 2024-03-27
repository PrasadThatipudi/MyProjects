// Cruds interface

// import java.util.List;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

interface iCruds
{
	void create(ArrayList<String> records);
	ArrayList<List<String>> getAllRecords();
	ArrayList<String> getFieldNames();
}