package student_project;

import java.util.Objects;

public class StudentData implements Comparable<Object> {
	//과목수
	public static final int SUBJECT = 3;
	
	//멤버변수 : 학번, 이름, 성별, 국어, 영어, 수학, 총점, 평균, 등급
	private int id;
	private String name;
	private String gender;
	private int kor;
	private int eng;
	private int math;
	private int total;
	private double avr;
	private char grade;
	
	//생성자 (default, overloading)
	public StudentData() {
		this(0, null, null, 0, 0, 0);
	}
	
	public StudentData(int id, String name, String gender, int kor, int eng, int math) {
		super();
		this.id = id;
		this.name = name;
		this.gender = gender;
		this.kor = kor;
		this.eng = eng;
		this.math = math;
		this.total = 0;
		this.avr = 0.0;
		this.grade = '\u0000';
	}
	
	public StudentData(int id, String name, String gender, int kor, int eng, int math, int total, double avr,
			char grade) {
		this(id, name, gender, kor, eng, math);
		this.total = total;
		this.avr = avr;
		this.grade = grade;
	}

	//인스턴스 멤버함수 : 총점 계산 
	public int calTotal() {
		return this.kor + this.eng + this.math;
	}

	//인스턴스 멤버함수 : 평균 계산 
	public double calAvr() {
		return (this.total / (double)SUBJECT);
	}
	
	//인스턴스 멤버함수 : 등급 계산 
	public char calGrade(double avr) {
		char grade = '\u0000';
		
		if(avr>=90.0) grade = 'A';
		else if(avr>=80.0) grade = 'B';
		else if(avr>=70.0) grade = 'C';
		else if(avr>=60.0) grade = 'D';
		else grade = 'F';
		
		return grade;
	}

	//overriding : hashcode - 학번
	@Override
	public int hashCode() {
		return Objects.hash(id);
	}

	//overriding : equals - 학번
	@Override
	public boolean equals(Object obj) {
		if(!(obj instanceof StudentData))
			throw new IllegalArgumentException("No StudentData class in this class");

		StudentData sd = (StudentData)obj;
		return (this.id == sd.id);
	}

	//overriding : compareTo - 총점
	@Override
	public int compareTo(Object o) {
		if(!(o instanceof StudentData))
			throw new IllegalArgumentException("No StudentData class in this class");

		StudentData sd = (StudentData)o;
		int value = 0;
		
		if(this.total < sd.total) value = -1;
		else if(this.total > sd.total) value = 1;
		return value;
	}

	//overriding : toString
	@Override
	public String toString() {
		return id + "\t" + name + "\t" + gender + "\t" + String.format("%3d", kor) + "점 \t" 
				+ String.format("%3d", eng) + "점 \t" + String.format("%3d", math) + "점 \t" 
				+ total + "점 \t" + String.format("%6.2f", avr) + "점  " + String.format("%2c", grade);
	}

	//getter & setter
	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getGender() {
		return gender;
	}

	public void setGender(String gender) {
		this.gender = gender;
	}

	public int getKor() {
		return kor;
	}

	public void setKor(int kor) {
		this.kor = kor;
	}

	public int getEng() {
		return eng;
	}

	public void setEng(int eng) {
		this.eng = eng;
	}

	public int getMath() {
		return math;
	}

	public void setMath(int math) {
		this.math = math;
	}

	public int getTotal() {
		return total;
	}

	public void setTotal(int total) {
		this.total = total;
	}

	public double getAvr() {
		return avr;
	}

	public void setAvr(double avr) {
		this.avr = avr;
	}

	public char getGrade() {
		return grade;
	}

	public void setGrade(char grade) {
		this.grade = grade;
	}
}
