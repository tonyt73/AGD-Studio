object frmEditorMessages: TfrmEditorMessages
  Left = 0
  Top = 0
  Width = 596
  Height = 361
  TabOrder = 0
  OnMouseActivate = FrameMouseActivate
  object panCharacterSet: TPanel
    Left = 0
    Top = 0
    Width = 596
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
  end
  object panContainer: TPanel
    Left = 0
    Top = 41
    Width = 596
    Height = 320
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitHeight = 323
    object Panel1: TPanel
      Left = 0
      Top = 0
      Width = 265
      Height = 320
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
      ExplicitHeight = 323
    end
    object Panel2: TPanel
      Left = 265
      Top = 0
      Width = 331
      Height = 320
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      ExplicitHeight = 323
      object Splitter1: TSplitter
        Left = 0
        Top = 0
        Width = 4
        Height = 320
        ExplicitHeight = 401
      end
    end
  end
end
