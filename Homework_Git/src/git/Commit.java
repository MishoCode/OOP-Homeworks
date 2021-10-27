package git;

import java.util.HashSet;
import java.util.Set;

public class Commit {
    private String message;
    //private String hash;
    private Set<String> addedFiles;
    private Set<String> removedFiles;

    public Commit(String message, Set<String> addedFiles, Set<String> removedFiles) {
        this.message = message;
        this.addedFiles = addedFiles;
        this.removedFiles = removedFiles;
    }

    public Set<String> getAddedFiles() {
        return addedFiles;
    }

    public Set<String> getRemovedFiles() {
        return removedFiles;
    }
}
