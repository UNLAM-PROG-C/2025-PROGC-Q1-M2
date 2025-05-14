import java.util.Random;

class ShadowClone implements Runnable 
{
    private int id;
    private int chakra;
    private int gainedLevel;
    private Random rand;

    public ShadowClone (int id)
    {
        this.id = id;
        this.rand = new Random();
        this.chakra = 5 + rand.nextInt(6); // Chakra: 5 to 10
        this.gainedLevel = 0;
    }

    @Override
    public void run()
    {
        for (int i = 0; i < this.chakra; i++)
        {
            try
            {
                Thread.sleep(100 + rand.nextInt(101)); // 100 to 200 ms
            } catch (InterruptedException e)
             {
                e.printStackTrace();
             }

            if (rand.nextBoolean()) { // 50% chance
                this.gainedLevel++;
            }
        }

        System.out.println("Clone #" + this.id + " gained " + this.gainedLevel + " levels (chakra: " + this.chakra + ").");
    }

    public int getGainedLevel()
    {
        return gainedLevel;
    }

    public int getChakra()
    {
        return chakra;
    }
}