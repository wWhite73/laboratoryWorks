import java.awt.dnd.DnDConstants;
import java.awt.dnd.DropTarget;
import java.awt.dnd.DropTargetDropEvent;
import java.awt.datatransfer.DataFlavor;
import java.io.File;
import java.util.List;

public class FileDropTarget extends DropTarget {
    private ImagePanel panel;

    public FileDropTarget(ImagePanel panel) {
        this.panel = panel;
    }

    public synchronized void drop(DropTargetDropEvent evt) {
        evt.acceptDrop(DnDConstants.ACTION_COPY);
        List<File> droppedFiles;
        try {
            droppedFiles = (List<File>) evt.getTransferable().getTransferData(DataFlavor.javaFileListFlavor);
            for (File file : droppedFiles) {
                BMPProcessor.processBMP(file, panel);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}