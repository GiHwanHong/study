get_filename_component(DEFAULT_QT_ZLIB_DIR "${QT_QTGUI_INCLUDE_DIR}/../../src/3rdparty/zlib"  ABSOLUTE)
set(QT_ZLIB_DIR ${DEFAULT_QT_ZLIB_DIR} CACHE PATH "Qt�� 3rdparty/zlib ���丮 ��ġ")
if(NOT QT_ZLIB_DIR)
  message(SEND_ERROR "QT_ZLIB_DIR�� �����Ǿ� ���� �ʽ��ϴ�.")
endif()
include_directories(${QT_ZLIB_DIR})

