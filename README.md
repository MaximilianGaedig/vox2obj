# vox2obj

vox2obj is a simple program to convert .vox file into obj file format.

## Usage

```ts
import vox2obj from 'vox2obj';
import { readFileSync,writeFileSync } from 'fs';

writeFileSync('out.obj', vox2obj(readFileSync('in.vox')));
```

## Credits

Thanks to @cedricpinson for the Initial project, I only made it into a node native module
