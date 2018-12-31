object frmAssetSelection: TfrmAssetSelection
  Left = 0
  Top = 0
  Width = 452
  Height = 634
  TabOrder = 0
  object sbxList: TScrollBox
    Left = 0
    Top = 0
    Width = 452
    Height = 634
    VertScrollBar.Smooth = True
    VertScrollBar.Style = ssFlat
    VertScrollBar.Tracking = True
    Align = alClient
    BorderStyle = bsNone
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 0
    OnMouseWheel = sbxListMouseWheel
    OnResize = sbxListResize
    object panList: TFlowPanel
      Left = 0
      Top = 0
      Width = 452
      Height = 634
      Align = alTop
      BevelOuter = bvNone
      ParentColor = True
      PopupMenu = popMenu
      ShowCaption = False
      TabOrder = 0
    end
  end
  object popMenu: TPopupMenu
    Left = 240
    Top = 96
    object mnuToggleLabels: TMenuItem
      AutoCheck = True
      Caption = 'Toggle Labels'
      Checked = True
      OnClick = mnuToggleLabelsClick
    end
  end
end
