package git;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.HashSet;
import java.util.Set;

public class Commit {
    public static final String TIME_FORMAT = "EEE MMM dd HH:mm yyyy";

    private final String message;
    private final String hash;
    private final LocalDateTime time;
    private final Stage stage;

    private String hexDigest(String input) {
        return new SHA1Digest().hexDigest(input);
    }

    public Commit(String message, Stage stage) {
        this.message = message;
        this.stage = stage;
        this.time = LocalDateTime.now();
        this.hash = hexDigest(getDate() + message);
    }

    public Set<String> getAddedFiles() {
        return stage.getAddedFiles();
    }

    public Set<String> getRemovedFiles() {
        return stage.getRemovedFiles();
    }

    public String getHash() {
        return hash;
    }

    public String getDate() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern(TIME_FORMAT);
        return time.format(formatter);
    }

    @Override
    public String toString() {
        return String.format("commit %s\nDate: %s\n\n\t%s\n", hash, getDate(), message);
    }
}
