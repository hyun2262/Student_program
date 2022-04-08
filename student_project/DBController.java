package student_project;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import com.mysql.jdbc.PreparedStatement;

public class DBController {
	//데이터 입력 : insert 쿼리문
	public static int dataInsert(StudentData sd) {
		//데이터베이스 접속
		Connection con = DBUtil.getConnection();
		
		//데이터베이스 입력 반환값
		int result = 0;
		
		//데이터베이스 연결 확인
		if(con==null) System.out.println("MySQL 연결에 실패하였습니다.");
		
		//삽입 명령문 전달(학번, 이름, 성별, 국어, 영어, 수학, 총점, 평균, 등급)
		String insertQuery = "insert into student_db.student_tbl values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
		PreparedStatement ps = null;
		
		try {
			//insert query binding(id, name, gender, kor, eng, math, total, avr, grade)
			ps = (PreparedStatement)con.prepareStatement(insertQuery);
			ps.setInt(1, sd.getId());
			ps.setString(2, sd.getName());
			ps.setString(3, sd.getGender());
			ps.setInt(4, sd.getKor());
			ps.setInt(5, sd.getEng());
			ps.setInt(6, sd.getMath());
			ps.setInt(7, sd.getTotal());
			ps.setDouble(8, sd.getAvr());
			//등급 : 문자형을 String 값으로 변환
			ps.setString(9, String.valueOf(sd.getGrade()));		
			
			//쿼리 실행 명령
			result = ps.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			try {
				con.close();
				ps.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		
		//결과값 반환
		return result;
	}
	
	//데이터 조회 : select 쿼리문
	public static List<StudentData> dataSearch(String searchData, int num) {
		final int ID=1, NAME=2;
		//데이터베이스 접속
		Connection con = DBUtil.getConnection();

		//데이터베이스 연결 확인
		if(con==null) System.out.println("MySQL 연결에 실패하였습니다.");
		
		//데이터베이스 입력 반환값
		List<StudentData> list = new ArrayList<StudentData>();
		ResultSet resultSet = null;
		
		//조회 명령문 전달(학번, 이름)
		String searchQuery = null; 
		PreparedStatement ps = null;
		
		try {
			switch(num) {
			case ID : 
				searchQuery = "select* from student_db.student_tbl where id=?"; 
				//select query binding
				ps = (PreparedStatement)con.prepareStatement(searchQuery);
				ps.setInt(1, Integer.parseInt(searchData));	break;
			case NAME : 
				searchQuery = "select* from student_db.student_tbl where name=?";	
				//select query binding
				ps = (PreparedStatement)con.prepareStatement(searchQuery);
				ps.setString(1, searchData); break;
			}
			//쿼리 실행 명령
			resultSet = ps.executeQuery();
			
			//resultSet을 list에 저장함수 호출
			resultSetToList(resultSet, list);
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			try {
				con.close(); ps.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		
		//결과값 반환
		return list;
	}
	
	//전체 데이터 출력
	public static List<StudentData> dataSelect() {
		//데이터베이스 접속
		Connection con = DBUtil.getConnection();

		//데이터베이스 연결 확인
		if(con==null) System.out.println("MySQL 연결에 실패하였습니다.");
		
		//데이터베이스 입력 반환값
		List<StudentData> list = new ArrayList<StudentData>();
		ResultSet resultSet = null;
		
		//조회 명령문 전달(학번, 이름)
		String selectQuery = null; 
		PreparedStatement ps = null;
		
		try {
			//select query binding
			selectQuery = "select* from student_db.student_tbl"; 
			ps = (PreparedStatement)con.prepareStatement(selectQuery);
			
			//쿼리 실행 명령
			resultSet = ps.executeQuery();
			
			//resultSet을 list에 저장함수 호출
			resultSetToList(resultSet, list);
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			try {
				con.close(); ps.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		
		//결과값 반환
		return list;
	}

	public static List<StudentData> dataSort(int menu) {
		final int ID=1, NAME=2, TOTAL=3;
		//데이터베이스 접속
		Connection con = DBUtil.getConnection();

		//데이터베이스 연결 확인
		if(con==null) System.out.println("MySQL 연결에 실패하였습니다.");
		
		//데이터베이스 입력 반환값
		List<StudentData> list = new ArrayList<StudentData>();
		ResultSet resultSet = null;
		
		//조회 명령문 전달(학번, 이름)
		String sortQuery = null; 
		PreparedStatement ps = null;
		
		switch(menu) {
		case ID: sortQuery = "select* from student_db.student_tbl order by id"; break;
		case NAME: sortQuery = "select* from student_db.student_tbl order by name"; break;
		case TOTAL:	sortQuery = "select* from student_db.student_tbl order by total desc"; break;
		}
		
		try {
			//쿼리 실행 명령
			ps = (PreparedStatement)con.prepareStatement(sortQuery);
			resultSet = ps.executeQuery();
			
			//resultSet을 list에 저장함수 호출
			resultSetToList(resultSet, list);
			
			} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			try {
				con.close(); ps.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		
		//결과값 반환
		return list;
	}
	
	//resultSet을 list에 저장(id, name, gender, kor, eng, math, total, avr, grade)
	private static void resultSetToList(ResultSet resultSet, List<StudentData> list) {
		try {
			while(resultSet.next()) {
				int id = resultSet.getInt(1);
				String name = resultSet.getString(2);
				String gender = resultSet.getString(3);
				int kor = resultSet.getInt(4);
				int eng = resultSet.getInt(5);
				int math = resultSet.getInt(6);
				int total = resultSet.getInt(7);
				double avr = resultSet.getDouble(8);
				char grade = resultSet.getString(9).charAt(0);
				
				//StudentData 객체 생성하여 list에 추가
				StudentData sd = new StudentData(id, name, gender, kor, eng, math, total, avr, grade);
				list.add(sd);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	//데이터 수정
	public static int dataUpdate(StudentData sd, int menu) {
		final int KOR=1, ENG=2, MATH=3;
		//데이터베이스 접속
		Connection con = DBUtil.getConnection();
		
		//데이터베이스 입력 반환값
		int result = 0;
		
		//데이터베이스 연결 확인
		if(con==null) System.out.println("MySQL 연결에 실패하였습니다.");
		
		//수정 명령문 전달
		String updateQuery = null;
		PreparedStatement ps = null;

		try {
			//update query binding
			switch(menu) {
			case KOR: 
				updateQuery = "update student_db.student_tbl set kor=?, total=?, avr=?, grade=? where id=?"; 
				ps = (PreparedStatement)con.prepareStatement(updateQuery);
				ps.setInt(1, sd.getKor()); break;
			case ENG: 
				updateQuery = "update student_db.student_tbl set eng=?, total=?, avr=?, grade=? where id=?";
				ps = (PreparedStatement)con.prepareStatement(updateQuery);
				ps.setInt(1, sd.getEng()); break;
			case MATH: 
				updateQuery = "update student_db.student_tbl set math=?, total=?, avr=?, grade=? where id=?"; 
				ps = (PreparedStatement)con.prepareStatement(updateQuery);
				ps.setInt(1, sd.getMath());	break;
			}
			
			ps.setInt(2, sd.getTotal());
			ps.setDouble(3, sd.getAvr());
			ps.setString(4, String.valueOf(sd.getGrade()));
			ps.setInt(5, sd.getId());
			
			//쿼리 실행 명령
			result = ps.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			try {
				con.close(); ps.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		
		//결과값 반환
		return result;
	}
	
	//데이터 삭제
	public static int dataDelete(int id) {
		//데이터베이스 접속
		Connection con = DBUtil.getConnection();
		
		//데이터베이스 입력 반환값
		int result = 0;
		
		//데이터베이스 연결 확인
		if(con==null) System.out.println("MySQL 연결에 실패하였습니다.");
		
		//삭제 명령문 전달(학번)
		String deleteQuery = "delete from student_db.student_tbl where id=?";
		PreparedStatement ps = null;
		
		try {
			//delete query binding
			ps = (PreparedStatement)con.prepareStatement(deleteQuery);
			ps.setInt(1, id);
			
			//쿼리 실행 명령
			result = ps.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			try {
				con.close(); ps.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		
		//결과값 반환
		return result;
	}
	
}
