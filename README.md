# Boilerplate

A simple boilerplate to start using [asm-dom](https://github.com/mbasso/asm-dom) with CRA-like configuration
This includes:

- `asm-dom`
- `CPX support: JSX like syntax in C++`
- `parcel-bundler` (`npm i --save-dev parcel-bundler@1.12.3`)
- `autoprefixer`

The boilerplate automatically compiles C++ code to WebAssembly and asm.js, the client will dynamically require the first if supported, the second otherwise.

# Project Structure

```
.
├── glue/
|   └── load.js
├── src/
│   ├── assets
|   |   └── *all css and media files
|   ├── pages
|   |   └── *all your page.cpp files
|   ├── App.cpp <- your App file
│   └── index.js <- loading WASM and importing CSS
├── includes/ASM_DOM/
|   ├── config.h <- your routing system and forward-declaration for all your pages
|   ├── globals.h <- your global variables
│   └── *all other project header files
├── Makefile
├── nodemon.json
├── .babelrc
├── .postcssrc
├── .gitignore
├──index.html
└── package.json
```


## Prerequisites

- [node](https://nodejs.org)
- [npm](http://npmjs.com/)
- [make](https://www.gnu.org/software/make/)
- [emcc](http://webassembly.org/getting-started/developers-guide/)
- [java](https://www.java.com)

NOTE: PLEASE USE emcc 1.40.1, NEW VERSIONS WILL NOT WORK

Please make sure to have `emcc` set as an environment variable and the lastest version of `node` to make parcel work. So, to validate the installation, please run the following commands:

```bash
node -v
npm -v
make -v
emcc -v
java -version
```

## Getting started

Clone and install dependencies:

```bash
git clone https://github.com/mbasso/asm-dom-boilerplate.git
cd asm-dom-boilerplate
npm install # or make install

# if you are using windows, you have to make a little change to the Makefile in the root of the project, just open it and follow the instructions at the top

make start
```

Then open `http://localhost:1234` to see the example app. You can now edit `App.cpp` and rerun `make start` to recompile and see the changes.

## Building for Production

```bash
make
```

This will be in the /dist folder

## Makefile

By default the boilerplate preprocess the `.cpp` files in the `src` folder with [gccx](https://github.com/mbasso/gccx) and automatically includes them when compiling. If you want to include external dependencies or add some C flags, you can modify the `Makefile` in the root of the project.

## CSS

[Parcel uses PostCSS plugins to manage CSS assets](https://parceljs.org/transforms.html#postcss).
The boilerplate includes `autoprefixer` for vendor prefixing, you can find and modify the PostCSS setup in `.postcssrc`.