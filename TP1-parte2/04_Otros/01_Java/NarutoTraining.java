public class NarutoTraining {
    public static void create_start_threads(ShadowClone[] clones, Thread[] threads)
    {
        for (int i = 0; i < clones.length; i++)
         {
            clones[i] = new ShadowClone(i + 1);
            threads[i] = new Thread(clones[i]);
            threads[i].start();
         }
    }

    public static void join_thread(Thread[] threads) throws InterruptedException
    {
         for (Thread thread : threads)
         {
            thread.join();
         }
    }

    public static void main(String[] args) throws InterruptedException {
        int cloneCount = Integer.parseInt(args[0]);
        ShadowClone[] clones = new ShadowClone[cloneCount];
        Thread[] threads = new Thread[cloneCount];

        long startTime = System.currentTimeMillis();

        create_start_threads(clones,threads);

        join_thread(threads);

        long endTime = System.currentTimeMillis();
        int totalLevel = 0;

        for (ShadowClone c : clones) {
            totalLevel += c.getGainedLevel();
        }

        System.out.println("Total level gained by Naruto: " + totalLevel);
        System.out.println("Execution time: " + (endTime - startTime) + " ms");
    }
}