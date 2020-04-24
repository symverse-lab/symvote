// Compile: javac -cp jna-5.5.0.jar VoteExample.java Vote.java
// Run: java -cp .:jna-5.5.0.jar VoteExample

// import com.sun.jna.*;
// import java.util.*;
// import java.lang.Long;

public class VoteExample {
    public static final int TEST = 0;
    public static final int TEST_OPTION = 0;

    public static void main(String argv[]) throws InterruptedException {
        Vote vote = new Vote();
        if (TEST == 0) {
            vote.fullScenario(TEST_OPTION);
        } else if (TEST == 1) {
            vote.fullScenario2(TEST_OPTION);
        } else {

        }
    }
}
