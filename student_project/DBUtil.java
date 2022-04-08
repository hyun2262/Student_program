package student_project;

import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class DBUtil {
	//데이터베이스 연결
	public static Connection getConnection() {
		Connection con = null;
		FileReader fr = null;
		
		try {
			//properties 파일 읽어오기
			fr = new FileReader("src\\student_project\\db.properties");
			Properties properties = new Properties();
			properties.load(fr);
			
			//db.properties 데이터 불러오기
			String DRIVER = properties.getProperty("DRIVER");
			String URL = properties.getProperty("URL");
			String userID = properties.getProperty("userID");
			String userPW = properties.getProperty("userPW");
			
			//드라이버 적재
			Class.forName(DRIVER);
			
			//데이터베이스 연결
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
