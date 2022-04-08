package student_project;

import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class DBUtil {
	//�����ͺ��̽� ����
	public static Connection getConnection() {
		Connection con = null;
		FileReader fr = null;
		
		try {
			//properties ���� �о����
			fr = new FileReader("src\\student_project\\db.properties");
			Properties properties = new Properties();
			properties.load(fr);
			
			//db.properties ������ �ҷ�����
			String DRIVER = properties.getProperty("DRIVER");
			String URL = properties.getProperty("URL");
			String userID = properties.getProperty("userID");
			String userPW = properties.getProperty("userPW");
			
			//����̹� ����
			Class.forName(DRIVER);
			
			//�����ͺ��̽� ����
			con = (Connection) DriverManager.getConnection(URL, userID, userPW);
			
		} catch (IOException e) {
			System.out.println("db.properties connection failed.");
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			System.out.println("DB connection failed.");
			e.printStackTrace();
		} catch (SQLException e) {
			System.out.println("DB connection failed.");
			e.printStackTrace();
		} finally {
			try {
				fr.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		
		return con;
	}
}
