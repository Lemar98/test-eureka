{
  "targets": [
    {
      "target_name": "userChecker",
      "sources": [ "userChecker.cc" ],
      "include_dirs": [
        "<!(node -e \"require('node-addon-api').include\")"
      ],
      "libraries": [
        "netapi32.lib"
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "defines": [
        "_WIN32_WINNT=0x0601",
        "NAPI_DISABLE_CPP_EXCEPTIONS"
      ]
    }
  ]
}