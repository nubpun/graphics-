object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 730
  ClientWidth = 1016
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  WindowState = wsMaximized
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Timer1: TTimer
    Interval = 10
    OnTimer = Timer1Timer
    Left = 352
    Top = 160
  end
  object MainMenu1: TMainMenu
    Left = 8
    Top = 16
    object N1: TMenuItem
      Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      OnClick = N2Click
    end
    object N3: TMenuItem
      Caption = #1042#1099#1093#1086#1076
      OnClick = N3Click
    end
  end
end
