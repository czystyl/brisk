open Brisk;

type attribute = [ Layout.style | BriskEffectView.style];

type style = list(attribute);

let material = material => `Material(material);
let blendingMode = blendingMode => `BlendingMode(blendingMode);
let emphasized = emphasized => `Emphasized(emphasized);
let effectState = effectState => `EffectState(effectState);

let component = nativeComponent("EffectView");

let make = (~style: style=[], children) =>
  component((_: Hooks.empty) =>
    {
      make: () => {
        let view = BriskEffectView.make();
        {view, layoutNode: Layout.Node.make(~style, view)};
      },
      configureInstance: (~isFirstRender as _, {view} as node) => {
        style
        |> List.iter(attribute =>
             switch (attribute) {
             | #BriskEffectView.style =>
               BriskEffectView.setStyle(view, attribute)
             | #Layout.style => ()
             }
           );
        node;
      },
      children,
    }
  );

let createElement = (~style=[], ~children, ()) =>
  element(make(~style, listToElement(children)));
