public class EnergyConsumptionData {
  private double dram;

  private double cpu;

  private double pack;

  public void setData(double[] data) {
    if (data != null && data.length == 3) {
      this.dram = data[0];
      this.cpu = data[1];
      this.pack = data[2];
    } 
  }

  public double getDram() {
    return this.dram;
  }

  public double getCpu() {
    return this.cpu;
  }

  public double getPackage() {
    return this.pack;
  }
}
