public class ExpCosFunction implements Function {
    @Override
    public double f(double x, double y) {
        return Math.exp(Math.cos(Math.pow(x, 2) + y));
    }
}
