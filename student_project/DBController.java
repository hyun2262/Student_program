package student_project;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import com.mysql.jdbc.PreparedStatement;

public class DBController {
	//������ �Է� : insert ������
	public static int dataInsert(StudentData sd) {
		//�����ͺ��̽� ����
		Connection con = DBUtil.getConnection();
		
		//�����ͺ��̽� �Է� ��ȯ��
		int result = 0;
		
		//�����ͺ��̽� ���� Ȯ��
		if(con==null) System.out.println("MySQL ���ῡ �����Ͽ����ϴ�.");
		
		//���� ��ɹ� ����(�й�, �̸�, ����, ����, ����, ����, ����, ���, ���)
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
			//��� : �������� String ������ ��ȯ
			ps.setString(9, String.valueOf(sd.getGrade()));		
			
			//���� ���� ���
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
		
		//����� ��ȯ
		return result;
	}
	
	//������ ��ȸ : select ������
	public static List<StudentData> dataSearch(String searchData, int num) {
		final int ID=1, NAME=2;
		//�����ͺ��̽� ����
		Connection con = DBUtil.getConnection();

		//�����ͺ��̽� ���� Ȯ��
		if(con==null) System.out.println("MySQL ���ῡ �����Ͽ����ϴ�.");
		
		//�����ͺ��̽� �Է� ��ȯ��
		List<StudentData> list = new ArrayList<StudentData>();
		ResultSet resultSet = null;
		
		//��ȸ ��ɹ� ����(�й�, �̸�)
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
			//���� ���� ���
			resultSet = ps.executeQuery();
			
			//resultSet�� list�� �����Լ� ȣ��
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
		
		//����� ��ȯ
		return list;
	}
	
	//��ü ������ ���
	public static List<StudentData> dataSelect() {
		//�����ͺ��̽� ����
		Connection con = DBUtil.getConnection();

		//�����ͺ��̽� ���� Ȯ��
		if(con==null) System.out.println("MySQL ���ῡ �����Ͽ����ϴ�.");
		
		//�����ͺ��̽� �Է� ��ȯ��
		List<StudentData> list = new ArrayList<StudentData>();
		ResultSet resultSet = null;
		
		//��ȸ ��ɹ� ����(�й�, �̸�)
		String selectQuery = null; 
		PreparedStatement ps = null;
		
		try {
			//select query binding
			selectQuery = "select* from student_db.student_tbl"; 
			ps = (PreparedStatement)con.prepareStatement(selectQuery);
			
			//���� ���� ���
			resultSet = ps.executeQuery();
			
			//resultSet�� list�� �����Լ� ȣ��
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
		
		//����� ��ȯ
		return list;
	}

	public static List<StudentData> dataSort(int menu) {
		final int ID=1, NAME=2, TOTAL=3;
		//�����ͺ��̽� ����
		Connection con = DBUtil.getConnection();

		//�����ͺ��̽� ���� Ȯ��
		if(con==null) System.out.println("MySQL ���ῡ �����Ͽ����ϴ�.");
		
		//�����ͺ��̽� �Է� ��ȯ��
		List<StudentData> list = new ArrayList<StudentData>();
		ResultSet resultSet = null;
		
		//��ȸ ��ɹ� ����(�й�, �̸�)
		String sortQuery = null; 
		PreparedStatement ps = null;
		
		switch(menu) {
		case ID: sortQuery = "select* from student_db.student_tbl order by id"; break;
		case NAME: sortQuery = "select* from student_db.student_tbl order by name"; break;
		case TOTAL:	sortQuery = "select* from student_db.student_tbl order by total desc"; break;
		}
		
		try {
			//���� ���� ���
			ps = (PreparedStatement)con.prepareStatement(sortQuery);
			resultSet = ps.executeQuery();
			
			//resultSet�� list�� �����Լ� ȣ��
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
		
		//����� ��ȯ
		return list;
	}
	
	//resultSet�� list�� ����(id, name, gender, kor, eng, math, total, avr, grade)
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
				
				//StudentData ��ü �����Ͽ� list�� �߰�
				StudentData sd = new StudentData(id, name, gender, kor, eng, math, total, avr, grade);
				list.add(sd);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	//������ ����
	public static int dataUpdate(StudentData sd, int menu) {
		final int KOR=1, ENG=2, MATH=3;
		//�����ͺ��̽� ����
		Connection con = DBUtil.getConnection();
		
		//�����ͺ��̽� �Է� ��ȯ��
		int result = 0;
		
		//�����ͺ��̽� ���� Ȯ��
		if(con==null) System.out.println("MySQL ���ῡ �����Ͽ����ϴ�.");
		
		//���� ��ɹ� ����
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
			
			//���� ���� ���
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
		
		//����� ��ȯ
		return result;
	}
	
	//������ ����
	public static int dataDelete(int id) {
		//�����ͺ��̽� ����
		Connection con = DBUtil.getConnection();
		
		//�����ͺ��̽� �Է� ��ȯ��
		int result = 0;
		
		//�����ͺ��̽� ���� Ȯ��
		if(con==null) System.out.println("MySQL ���ῡ �����Ͽ����ϴ�.");
		
		//���� ��ɹ� ����(�й�)
		String deleteQuery = "delete from student_db.student_tbl where id=?";
		PreparedStatement ps = null;
		
		try {
			//delete query binding
			ps = (PreparedStatement)con.prepareStatement(deleteQuery);
			ps.setInt(1, id);
			
			//���� ���� ���
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
		
		//����� ��ȯ
		return result;
	}
	
}
