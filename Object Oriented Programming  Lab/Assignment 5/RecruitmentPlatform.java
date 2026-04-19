class User {
    protected String username;
    protected String email;
    protected boolean isLoggedIn;
    // Constructor
    public User(String username, String email) {
        this.username = username;
        this.email = email;
        this.isLoggedIn = false;
    }
    // Methods to login/logout
    public void login() {
        isLoggedIn = true;
        System.out.println(username + " has logged in.");
    }
    public void logout() {
        isLoggedIn = false;
        System.out.println(username + " has logged out.");
    }
    public void displayInfo() {
        System.out.println("Username: " + username);
        System.out.println("Email: " + email);
        System.out.println("Login Status: " + (isLoggedIn ? "Logged In" : "Logged Out"));
    }
}
// Candidate subclass
class Candidate extends User {
    private String resume;
    public Candidate(String username, String email) {
        super(username, email);
        this.resume = "";
    }
    public void uploadResume(String resume) {
        this.resume = resume;
        System.out.println(username + " uploaded resume: " + resume);
    }
    public void applyJob(String jobTitle) {
        System.out.println(username + " applied for job: " + jobTitle);
    }
}
// Recruiter subclass
class Recruiter extends User {
    public Recruiter(String username, String email) {
        super(username, email);
    }

    public void postJob(String jobTitle) {
        System.out.println(username + " posted a new job: " + jobTitle);
    }

    public void shortlistCandidate(String candidateName) {
        System.out.println(username + " shortlisted candidate: " + candidateName);
    }
}
// Admin subclass
class Admin extends User {
    public Admin(String username, String email) {
        super(username, email);
    }
    public void manageUsers() {
        System.out.println(username + " is managing users.");
    }
    public void generateReport() {
        System.out.println(username + " generated a report.");
    }
}
public class RecruitmentPlatform {
    public static void main(String[] args) {
        // Candidate
        Candidate candidate = new Candidate("Alice", "alice@example.com");
        candidate.login();
        candidate.uploadResume("Alice_Resume.pdf");
        candidate.applyJob("Software Engineer");
        candidate.displayInfo();
        candidate.logout();
        System.out.println("-----------------------------------");
        // Recruiter
        Recruiter recruiter = new Recruiter("Bob", "bob@company.com");
        recruiter.login();
        recruiter.postJob("Frontend Developer");
        recruiter.shortlistCandidate("Alice");
        recruiter.displayInfo();
        recruiter.logout();
        System.out.println("-----------------------------------");
        // Admin
        Admin admin = new Admin("Carol", "carol@admin.com");
        admin.login();
        admin.manageUsers();
        admin.generateReport();
        admin.displayInfo();
        admin.logout();
    }
}