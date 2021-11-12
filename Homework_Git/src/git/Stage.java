package git;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class Stage {
    private final Set<String> addedFiles;
    private final Set<String> removedFiles;

    public Stage() {
        addedFiles = new HashSet<>();
        removedFiles = new HashSet<>();
    }

    public Set<String> getAddedFiles() {
        return addedFiles;
    }

    public Set<String> getRemovedFiles() {
        return removedFiles;
    }

    public boolean contains(String file) {
        return addedFiles.contains(file);
    }

    public void add(String[] files) {
        Collections.addAll(addedFiles, files);
    }

    public void remove(String[] files) {
        for (String file : files) {
            if (addedFiles.contains(file)) {
                addedFiles.remove(file);
                continue;
            }

            removedFiles.add(file);
        }
    }

    public int getChangedFilesCount() {
        return addedFiles.size() + removedFiles.size();
    }
}
