import javax.swing.*;
import java.awt.*;

public class BMPApp extends JFrame {
    public BMPApp() {
        ImagePanel panel = new ImagePanel();
        panel.setDropTarget(new FileDropTarget(panel));
        add(panel, BorderLayout.CENTER);
        setSize(700, 700);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(BMPApp::new);
    }
}