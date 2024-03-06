public class CosFunction implements Function {
    @Override
    public double f(double x, double y) {
        return Math.cos(x * Math.exp(y));
    }
}
