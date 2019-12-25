import org.dacapo.harness.Callback;
import org.dacapo.harness.CommandLineArgs;

public class EnergyConsumptionCallback extends Callback {
  private EnergyConsumptionData consumptionBefore;
  private EnergyConsumptionData consumptionAfter;

  public EnergyConsumptionCallback(CommandLineArgs args) {
    super(args);
    consumptionBefore = new EnergyConsumptionData();
    consumptionAfter = new EnergyConsumptionData();
    EnergyCheckUtils.ProfileInit();
  }

  /* Immediately prior to start of the benchmark */
  @Override
  public void start(String benchmark) {
    consumptionBefore.setData(EnergyCheckUtils.getEnergyStats());
    super.start(benchmark);
  };

  /* Immediately after the end of the benchmark */
  @Override
  public void stop(long duration) {
    super.stop(duration);
    consumptionAfter.setData(EnergyCheckUtils.getEnergyStats()); 
  };

  @Override
  public void complete(String benchmark, boolean valid) {
    super.complete(benchmark, valid);
    System.err.println("DRAM consumption: "+(consumptionAfter.getDram()-consumptionBefore.getDram()));
    System.err.println("CPU consumption: "+(consumptionAfter.getCpu()-consumptionBefore.getCpu()));
    System.err.println("PACKAGE consumption: "+(consumptionAfter.getPackage()-consumptionBefore.getPackage()));
    System.err.flush();
  };
}
