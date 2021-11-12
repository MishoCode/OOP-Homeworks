package git;

import java.util.*;

public class Repository {
    Stage stage;
    String currentBranch;
    Map<String, List<Commit>> branches;

    private void addNewCommit(Commit commit) {
        branches.get(currentBranch).add(commit);
    }

    private void clearFiles() {
        stage = new Stage();
    }

    private boolean isAlreadyCommitted(String file) {
        List<Commit> allCommits = branches.get(currentBranch);
        Set<String> allFiles = new HashSet<>();
        for (Commit commit : allCommits) {
            allFiles.addAll(commit.getAddedFiles());
            allFiles.removeAll(commit.getRemovedFiles());
        }

        for (String currentFile : allFiles) {
            if (currentFile.equals(file)) {
                return true;
            }
        }

        return false;
    }

    private Result getCommitsHistory(List<Commit> commits) {
        StringBuilder message = new StringBuilder();
        for (Commit commit : commits) {
            message.append(commit);
        }

        return new Result(true, message.toString());
    }

    public Repository() {
        stage = new Stage();
        currentBranch = "master";
        branches = new HashMap<>();
        branches.put(currentBranch, new LinkedList<>());
    }

    public Result add(String[] files) {
        for (String file : files) {
            if (stage.contains(file) || isAlreadyCommitted(file)) {
                String message = String.format("%s already exists.", file);
                return new Result(false, file + " already exists.");
            }
        }

        stage.add(files);

        String message = String.format("Added %s to stage.", String.join(", ", files));
        return new Result(true, message);
    }

    public Result commit(String message) {
        int changedFilesCount = stage.getChangedFilesCount();
        if (changedFilesCount == 0) {
            return new Result(false, "Nothing to commit, working tree clean.");
        }

        Commit head = new Commit(message, stage);
        addNewCommit(head);
        clearFiles();

        String resultMessage = String.format("%d files changed", changedFilesCount);
        return new Result(true, resultMessage);
    }

    public Result remove(String[] files) {
        for (String file : files) {
            if (!stage.contains(file) || !isAlreadyCommitted(file)) {
                String message = String.format("%s did not match any file.", file);
                return new Result(false, message);
            }
        }

        stage.remove(files);

        String message = String.format("Added %s files for removal", String.join(", ", files));
        return new Result(true, message);
    }

    public Commit getHead() {
        List<Commit> commits = branches.get(currentBranch);

        if (commits.isEmpty()) {
            return null;
        }

        return commits.get(commits.size() - 1);
    }

    public Result log() {
        List<Commit> commits = branches.get(currentBranch);
        Collections.reverse(commits);

        if (commits.isEmpty()) {
            String message = String.format("branch %s does not have any commits yet.", currentBranch);
            return new Result(false, message);
        }

        return getCommitsHistory(commits);
    }

    public String getBranch() {
        return currentBranch;
    }

    public Result createBranch(String name) {
        if (branches.containsKey(name)) {
            String message = String.format("branch %s already  exists.", name);
            return new Result(false, message);
        }

        List<Commit> commits = branches.get(currentBranch);
        branches.put(name, commits);

        String message = String.format("created branch %s.", name);
        return new Result(true, message);
    }

    public Result checkoutBranch(String name) {
        if (!branches.containsKey(name)) {
            String message = String.format("branch %s does not exist.", name);
            return new Result(false, message);
        }

        currentBranch = name;
        String message = String.format("switched to branch %s.", name);
        return new Result(true, message);
    }

    Result checkoutCommit(String hash) {
        List<Commit> commits = branches.get(currentBranch);

        boolean commitFound = false;
        int i = 0;
        while (i < commits.size()) {
            if (commits.get(i).getHash().equals(hash)) {
                commitFound = true;
                break;
            }
            i++;
        }

        if (commitFound) {
            branches.put(currentBranch, commits.subList(0, i + 1));
            String message = String.format("HEAD is now at %s.", hash);
            return new Result(true, message);
        }

        String message = String.format("commit %s does not exist.", hash);
        return new Result(false, message);
    }
}
