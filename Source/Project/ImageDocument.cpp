//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ImageDocument.h"
#include "DocumentManager.h"
#include "Graphics/GraphicsTypes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ImageDocument::ImageDocument(const String& name)
: Document(name)
, m_MultiFrame(false)
, m_CanModifyFrames(false)
, m_CanBeLocked(false)
, m_Width(0)
, m_Height(0)
, m_FramesLoaded(0)
{
    m_Type = "Image";
    m_SubType = "Single";
    m_Folder = "Images\\Images";
    m_SaveRefId = true;
    if (name != Unnamed) {
        RegisterProperty("Name", "Details", "The name of the image");
        RegisterProperty("Width", "Dimensions", "The width in pixels of the image");
        RegisterProperty("Height", "Dimensions", "The height in pixels of the image");
        RegisterProperty("Frames", "Dimensions", "The number of frames in the image");
        RegisterProperty("ImagesPerFrame", "Dimensions", "The number of separate AGD images used in a frame");
        // json loading properties
        m_PropertyMap["Image.Width"] = &m_Width;
        m_PropertyMap["Image.Height"] = &m_Height;
        m_PropertyMap["Image.Frames[]"] = &m_FrameLoader;
        m_PropertyMap["Image.Layers[].Name"] = &m_LayerName;
        m_PropertyMap["Image.Layers[].Data"] = &m_LayerData;
    }
    m_File = GetFile();
}
//---------------------------------------------------------------------------
void __fastcall ImageDocument::DoSave()
{
    Push("Image");
    Write("Width", m_Width);
    Write("Height", m_Height);
    ArrayStart("Frames");
    for (const auto& frame : m_Frames) {
        Write(frame);
    }
    ArrayEnd(); // Frames
    if (m_Layers.size() > 0) {
        ArrayStart("Layers");
        for (const auto& layer : m_Layers) {
            StartObject();
            Write("Name", layer.first);
            Write("Data", layer.second);
            EndObject();
        }
        ArrayEnd(); // Layers
    }
    DoSaveExtra();
    Pop(); // image
}
//---------------------------------------------------------------------------
void __fastcall ImageDocument::DoSaveExtra()
{
    // do nothing
}
//---------------------------------------------------------------------------
void __fastcall ImageDocument::OnEndObject(const String& object)
{
    if (object == "Image.Frames[]") {
        if (m_FramesLoaded < m_Frames.size()) {
            m_Frames[m_FramesLoaded] = m_FrameLoader;
        } else {
            m_Frames.push_back(m_FrameLoader);
        }
        m_FramesLoaded++;
    } else if (object == "Image.Layers[]") {
        m_Layers[m_LayerName] = m_LayerData;
    }
}
//---------------------------------------------------------------------------
int __fastcall ImageDocument::GetIndex() const
{
    return theDocumentManager.GetAsIndex(Id);
}
//---------------------------------------------------------------------------
int __fastcall ImageDocument::CountFrames() const
{
    return m_Frames.size();
}
//---------------------------------------------------------------------------
int __fastcall ImageDocument::CountImagesPerFrame() const
{
    const auto pc = theDocumentManager.ProjectConfig();
    if (pc) {
        const auto& mc = pc->MachineConfiguration();
        auto sx = mc.ImageSizing[m_ImageType].Step.cx;
        auto sy = mc.ImageSizing[m_ImageType].Step.cy;
        if (sx != 0 && sy != 0) {
            auto w = Width / sx;
            auto h = Height / sy;
            return w * h;
        }
    }
    return 1;
}
//---------------------------------------------------------------------------
void __fastcall ImageDocument::SetFrames(int frames)
{
    if (frames > 1 && frames != m_Frames.size()) {
        while (frames != m_Frames.size()) {
            frames > m_Frames.size() ? AddFrame() : DeleteFrame(m_Frames.size() - 1);
        }
    }
}
//---------------------------------------------------------------------------
String __fastcall ImageDocument::GetFrame(int frame) const
{
    if (0 <= frame && frame < m_Frames.size()) {
        return m_Frames[frame];
    }
    return "";
}
//---------------------------------------------------------------------------
void __fastcall ImageDocument::SetFrame(int frame, const String& data)
{
    if (0 <= frame && frame < m_Frames.size()) {
        m_Frames[frame] = data;
    }
}
//---------------------------------------------------------------------------
String __fastcall ImageDocument::GetHint(int frame) const
{
    if (0 <= frame && frame < m_Hints.size()) {
        return m_Hints[frame];
    }
    return "";
}
//---------------------------------------------------------------------------
bool __fastcall ImageDocument::AddFrame(int index, const String& hint)
{
    if (m_Frames.size() == 0 || (m_MultiFrame && m_CanModifyFrames)) {
        if (0 > index || index > m_Frames.size()) {
            m_Frames.push_back("");
            m_Hints.push_back(hint);
        } else {
            m_Frames.insert(m_Frames.begin() + index, "");
            m_Hints.insert(m_Hints.begin() + index, hint);
        }
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ImageDocument::DeleteFrame(int index)
{
    if (m_Frames.size() > 1 && m_CanModifyFrames && 0 <= index && index < m_Frames.size()) {
        // can only delete new frames; can't delete the first frame
        m_Frames.erase(m_Frames.begin() + index);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
int __fastcall ImageDocument::GetLayerCount() const
{
    return m_Layers.size();
}
//---------------------------------------------------------------------------
void __fastcall ImageDocument::AddLayer(const String& name, const String& value)
{
    if (!LayerExists(name)) {
        m_Layers[name] = value;
    }
}
//---------------------------------------------------------------------------
void __fastcall ImageDocument::ExtractSize(const String& extra)
{
    const auto pc = theDocumentManager.ProjectConfig();
    if (pc) {
        const auto& mc = pc->MachineConfiguration();
        m_Width = mc.ImageSizing[m_ImageType].Minimum.cx;
        m_Height = mc.ImageSizing[m_ImageType].Minimum.cy;
        if (extra != "") {
            // extract the size from the string
            auto pos = extra.Pos("x");
            if (pos > 0) {
                m_Width = StrToInt(extra.SubString(1, pos - 1));
                m_Height = StrToInt(extra.SubString(pos + 1, extra.Length()));
            }
        }
    }
}
//---------------------------------------------------------------------------
String __fastcall ImageDocument::GetLayer(const String& name)
{
    String value;
    if (LayerExists(name)) {
        value = m_Layers[name];
    }
    return value;
}
//---------------------------------------------------------------------------
void __fastcall ImageDocument::SetLayer(const String& name, const String& value)
{
    if (LayerExists(name)) {
        m_Layers[name] = value;
    }
}
//---------------------------------------------------------------------------
bool __fastcall ImageDocument::LayerExists(const String& name) const
{
    return m_Layers.count(name) == 1;
}
//---------------------------------------------------------------------------
bool __fastcall ImageDocument::IsFirstOfType() const
{
    return theDocumentManager.IsFirstOfType(this);
}
//---------------------------------------------------------------------------

