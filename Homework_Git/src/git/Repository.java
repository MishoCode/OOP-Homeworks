package git;

import java.util.*;

public class Repository {
    private Set<String> addedFiles = new HashSet<>();
    private Set<String> removedFiles = new HashSet<>();
    String currentBranch;
    Map<String, List<Commit>> branches;

    private void addNewCommit(Commit commit){
        branches.get(currentBranch).add(commit);
    }

    private void clearFiles(){
        addedFiles.clear();
        removedFiles.clear();
    }

    private boolean isAlreadyCommitted(String file){
        List<Commit> allCommits = branches.get(currentBranch);
        Set<String> allFiles = new HashSet<>();
        for(Commit commit : allCommits){
            allFiles.addAll(commit.getAddedFiles());
            allFiles.removeAll(commit.getRemovedFiles());
        }

        for(String currentFile : allFiles){
            if(currentFile.equals(file)){
                return true;
            }
        }

        return false;
    }

    public Result add(String[] files) {
        for (String file : files) {
            if (addedFiles.contains(file) || isAlreadyCommitted(file)) {
                String message = String.format("%s already exists.", file);
                return new Result(false, file + " already exists.");
            }
        }

        for(String file : files) {
            addedFiles.add(file);
        }

        String message = String.format("Added %s to stage.", String.join(", ", files));
        return new Result(true, message);
    }

    public Result commit(String message) {
        if (removedFiles.isEmpty() && addedFiles.isEmpty()) {
            return new Result(false, "Nothing to commit, working tree clean.");
        }

        Commit head = new Commit(message, addedFiles, removedFiles);
        addNewCommit(head);
        clearFiles();

        String resultMessage = String.format("%d files changed", addedFiles.size() + removedFiles.size());
        return new Result(true, resultMessage);
    }

    public Result remove(String[] files) {
        for (String file : files) {
            if (!addedFiles.contains(file)) {
                String message = String.format("%s did not match any file.", file);
                return new Result(false, message);
            }
        }

        for(String file : files){
            if(addedFiles.contains(file)){
                addedFiles.remove(file);
            }else{
                removedFiles.add(file);
            }
        }

        String message = String.format("Added %s files for removal", String.join(", ", files));
        return new Result(true, message);
    }
}
