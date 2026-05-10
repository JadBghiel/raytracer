# TEST:

we can preview the image without having sfml for now 

from root do this:
`make
./raytracer scenes/<whatever cfg file>
./test/snapshot.sh path/output.ppm
`
then the png will be rendered in screenshots/

# TODO
- SHOULD:

  - cone (implemented but awaiting testing)
  - rotation (parsed but not implemented yet)
  - drop shadows
- extra important stuff tho but at the end

  - multi threading
  - anti aliasing supersampling


# DONE

- primitive factory ✅
- light factory ✅
- parser (jad) ✅
- MUST:

  - sphere intersection ✅
  - plane intersection ✅
  - camera ray generation ✅
  - transformation ✅

- SHOULD:
  - cylinder ✅
