import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class Main {
    private static final Color[] mosaicColors = new Color[4];
    private static int mosaicWidth = 0;
    private static int mosaicHeight = 0;
    private static int blockWidth = 0;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            try {
                JFrame frame = new JFrame("Drawing App");
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.setSize(800, 600);

                JMenuBar menuBar = new JMenuBar();
                JMenu menu = new JMenu("Options");
                JMenuItem drawMenuItem = new JMenuItem("Draw");
                JMenuItem mosaicMenuItem = new JMenuItem("Мозаика");
                JMenuItem colorMenuItem = new JMenuItem("Выбрать цвет");
                menu.add(drawMenuItem);
                menu.add(mosaicMenuItem);
                menu.add(colorMenuItem);
                menuBar.add(menu);
                frame.setJMenuBar(menuBar);

                JPanel panel = new JPanel() {
                    @Override
                    protected void paintComponent(Graphics g) {
                        super.paintComponent(g);
                        if (mosaicWidth > 0 && mosaicHeight > 0 && blockWidth > 0) {
                            Random random = new Random();
                            int startX = (getWidth() - mosaicWidth) / 2;
                            int startY = (getHeight() - mosaicHeight) / 2;
                            for (int y = 0; y < mosaicHeight; y += blockWidth) {
                                for (int x = 0; x < mosaicWidth; x += blockWidth) {
                                    int effectiveBlockWidth = Math.min(blockWidth, mosaicWidth - x);
                                    int effectiveBlockHeight = Math.min(blockWidth, mosaicHeight - y);
                                    g.setColor(mosaicColors[random.nextInt(4)]);
                                    g.fillRect(startX + x, startY + y, effectiveBlockWidth, effectiveBlockHeight);
                                }
                            }
                        }
                    }
                };
                frame.add(panel);

                colorMenuItem.addActionListener(e -> {
                    try {
                        Color color = JColorChooser.showDialog(frame, "Выберите цвет", Color.BLACK);
                        if (color != null) {
                            panel.setBackground(color);
                        }
                    } catch (Exception ex) {
                        JOptionPane.showMessageDialog(frame, "Ошибка при выборе цвета: " + ex.getMessage());
                    }
                });

                mosaicMenuItem.addActionListener(e -> {
                    try {
                        String mosaicSize = JOptionPane.showInputDialog(frame, "Введите размер мозаики (ширина и высота)");
                        String[] sizes = mosaicSize.split("x");
                        mosaicWidth = Integer.parseInt(sizes[0]);
                        mosaicHeight = Integer.parseInt(sizes[1]);

                        String blockSize = JOptionPane.showInputDialog(frame, "Выберите размер блока мозаики (2X2, 4x4, 8x8)");
                        blockWidth = Integer.parseInt(blockSize.split("x")[0]);

                        for (int i = 0; i < 4; i++) {
                            mosaicColors[i] = JColorChooser.showDialog(frame, "Выберите цвет " + (i + 1), Color.BLACK);
                        }

                        panel.repaint();
                    } catch (Exception ex) {
                        JOptionPane.showMessageDialog(frame, "Ошибка при создании мозаики: " + ex.getMessage());
                    }
                });

                frame.setVisible(true);
            } catch (Exception ex) {
                System.out.println("Ошибка при создании приложения: " + ex.getMessage());
                ex.printStackTrace();
            }
        });
    }
}
