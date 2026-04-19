import student.records.StudentRecord;
import student.attendance.Attendance;
import student.fees.Fees;

public class MainStudent {
    public static void main(String[] args) {
        StudentRecord s = new StudentRecord();
        Attendance a = new Attendance();
        Fees f = new Fees();

        s.showDetails();
        a.markAttendance();
        f.payFees();
    }
}
