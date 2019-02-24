object frmEditorJumpTable: TfrmEditorJumpTable
  Left = 0
  Top = 0
  Width = 887
  Height = 720
  TabOrder = 0
  OnMouseActivate = FrameMouseActivate
  OnResize = FrameResize
  object imgView: TImage
    Left = 71
    Top = 71
    Width = 757
    Height = 590
  end
  object ActionList1: TActionList
    Left = 72
    Top = 16
    object actLeft: TAction
      Caption = 'actLeft'
      ShortCut = 37
      OnExecute = actLeftExecute
    end
    object actRight: TAction
      Caption = 'actRight'
      ShortCut = 39
      OnExecute = actRightExecute
    end
    object actUp: TAction
      Caption = 'actUp'
      ShortCut = 38
      OnExecute = actUpExecute
    end
    object actDown: TAction
      Caption = 'actDown'
      ShortCut = 40
      OnExecute = actDownExecute
    end
  end
end
