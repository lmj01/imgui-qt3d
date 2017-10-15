#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H

#include <functional>
#include <QSize>
#include <QEntity>

class ImguiQt3DWindow;

namespace Qt3DRender {
class QBuffer;
class QTexture2D;
class QMaterial;
class QLayer;
class QGeometryRenderer;
class QShaderProgram;
class QScissorTest;
}

struct ImDrawCmd;

class ImguiManager {
public:
    typedef std::function<void()> FrameFunc;
    void setFrameFunc(FrameFunc f) { m_frame = f; }

    void setWindow(ImguiQt3DWindow *window) { m_window = window; }

    void initialize(Qt3DCore::QEntity *rootEntity);

private:
    struct CmdListEntry;
    void resizePool(CmdListEntry *e, int count);
    Qt3DRender::QMaterial *buildMaterial(Qt3DRender::QScissorTest **scissor);
    void updateGeometry(CmdListEntry *e, int idx, const ImDrawCmd *cmd, int vertexCount, int indexCount, const void *indexOffset);
    void update3D();

    FrameFunc m_frame = nullptr;
    ImguiQt3DWindow *m_window = nullptr;

    Qt3DCore::QEntity *m_rootEntity = nullptr;
    Qt3DRender::QTexture2D *m_atlasTex = nullptr;
    Qt3DRender::QShaderProgram *m_guiProg = nullptr;

    struct CmdEntry {
        Qt3DCore::QEntity *entity = nullptr;
        Qt3DRender::QGeometryRenderer *geomRenderer = nullptr;
        Qt3DRender::QScissorTest *scissor = nullptr;
    };

    struct CmdListEntry {
        Qt3DRender::QBuffer *vbuf = nullptr;
        Qt3DRender::QBuffer *ibuf = nullptr;
        QVector<CmdEntry> cmds;
        int activeCount = 0;
    };

    QVector<CmdListEntry> m_cmdList;
};

#endif