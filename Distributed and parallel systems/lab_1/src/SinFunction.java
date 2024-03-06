public class SinFunction implements Function {
    @Override
    public double f(double x, double y) {
        return Math.sin(x + 2 * y);
    }
}
