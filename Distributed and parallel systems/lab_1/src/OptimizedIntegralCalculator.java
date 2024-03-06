import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;

public class OptimizedIntegralCalculator {
    private final Function function;
    private final double a;
    private final double b;
    private final double c;
    private final double d;
    private final int n;
    private final int m;

    public OptimizedIntegralCalculator(Function function, double a, double b, double c, double d, int n, int m) {
        this.function = function;
        this.a = a;
        this.b = b;
        this.c = c;
        this.d = d;
        this.n = n;
        this.m = m;
    }

    public double calculate() {
        double dx = (b - a) / n;
        double dy = (d - c) / m;

        ForkJoinPool pool = new ForkJoinPool();
        double integral = pool.invoke(new IntegralTask(a, b, c, d, n, m, dx, dy, function));
        pool.shutdown();

        return integral;
    }

    private class IntegralTask extends RecursiveTask<Double> {
        private final double a, b, c, d, dx, dy;
        private final int n, m;
        private final Function function;

        public IntegralTask(double a, double b, double c, double d, int n, int m, double dx, double dy, Function function) {
            this.a = a;
            this.b = b;
            this.c = c;
            this.d = d;
            this.n = n;
            this.m = m;
            this.dx = dx;
            this.dy = dy;
            this.function = function;
        }

        @Override
        protected Double compute() {
            if (n <= 1000 && m <= 1000) { // условие разделения задачи на подзадачи
                double sum = 0;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        double x = a + i * dx + dx / 2;
                        double y = c + j * dy + dy / 2;
                        double f = function.f(x, y);
                        sum += f * dx * dy;
                    }
                }
                return sum;
            } else {
                int n1 = n / 2;
                int n2 = n - n1;
                int m1 = m / 2;
                int m2 = m - m1;
                IntegralTask task1 = new IntegralTask(a, a + n1 * dx, c, c + m1 * dy, n1, m1, dx, dy, function);
                IntegralTask task2 = new IntegralTask(a + n1 * dx, b, c, c + m1 * dy, n2, m1, dx, dy, function);
                IntegralTask task3 = new IntegralTask(a, a + n1 * dx, c + m1 * dy, d, n1, m2, dx, dy, function);
                IntegralTask task4 = new IntegralTask(a + n1 * dx, b, c + m1 * dy, d, n2, m2, dx, dy, function);
                invokeAll(task1, task2, task3, task4);
                return task1.join() + task2.join() + task3.join() + task4.join();
            }
        }
    }
}
