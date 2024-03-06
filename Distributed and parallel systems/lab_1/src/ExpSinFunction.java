public class ExpSinFunction implements Function {
    @Override
    public double f(double x, double y) {
        return Math.exp(x) * Math.sin(y);
    }
}
