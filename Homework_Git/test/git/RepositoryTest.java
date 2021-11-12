package git;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

public class RepositoryTest {
    private Repository repository;

    @Before
    public void setUp() {
        repository = new Repository();
    }

    @Test
    public void testRepoInitialization() {
        assertNull(repository.getHead());
        assertEquals("master", repository.getBranch());
    }

}
