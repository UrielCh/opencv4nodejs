{
	"targets": [{
		"target_name": "opencv4nodejs",
		"defines": [
			"<!@(node ./bin/install.js OPENCV4NODEJS_DEFINES)",
		],
		'dependencies': [
    		"<!(node -p \"require('node-addon-api').targets\"):node_addon_api_except",
		],
		"include_dirs" : [
			"<!@(node ./bin/install.js OPENCV4NODEJS_INCLUDES)",
			"cc",
			"cc/core",
            "<!(node -p \"require('node-addon-api').include_dir\")",
			"cc/native-node-utils",
		],
		"libraries": [
			"<!@(node ./bin/install.js OPENCV4NODEJS_LIBRARIES)",
		],
		'defines': [],
		"sources": [
			"cc/opencv4nodejs.cc",
			"cc/core/core.cc",
			"cc/core/coreConstants.cc",
		],
		"cflags" : [
			"-std=c++17",
		],
		"cflags!" : [
			"-std=c++17",
			"-fno-exceptions",
		],
		"cflags_cc!": [
			"-std=c++17",
			"-fno-rtti",
			"-fno-exceptions",
		],
		"ldflags" : [
			"-Wl,-rpath,'$$ORIGIN'"
		],
		"xcode_settings": {
			"OTHER_CFLAGS": [
				"-std=c++17",
				"-stdlib=libc++",
				"-ferror-limit=5"
			],
			"GCC_ENABLE_CPP_EXCEPTIONS": "YES",
			"MACOSX_DEPLOYMENT_TARGET": "11.0"
		},

		"conditions": [
			[ "OS==\"win\"", {
				"cflags": [
					"-Wall"
				],
				"defines": [
					"WIN",
					"_HAS_EXCEPTIONS=1"
				],
				"msvs_settings": {
					"VCCLCompilerTool": {
						"ExceptionHandling": 2,
						"RuntimeLibrary": 2
					},
				}
			}],
	        ["OS==\"mac\"",
	          {
				 "cflags+": ["-fvisibility=hidden"],
				 "cflags": [
					 "-fvisibility=hidden",
	                 "-std=c++17",
    	             "-Wno-error=deprecated-declarations"
	            ],
				"xcode_settings": {
                       "GCC_SYMBOLS_PRIVATE_EXTERN": "YES", # -fvisibility=hidden
                },
	            "link_settings": {
	              "libraries": [
					"-Wl,-rpath,@loader_path/../../../opencv-build/opencv/build/lib"
	              ],
	            }
	          }
	        ]
		],

		"configurations": {
			"Debug": {
				"cflags": ["--coverage"],
				"ldflags": ["--coverage"]
			},
    	}
	}]
}
