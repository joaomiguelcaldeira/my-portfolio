/*****************************
Projeto 2 - Computacao Grafica
93729 - Joao Caldeira
93730 - Joao Cardoso
93748 - Rafael Candeias
*****************************/

// --------------------------- global Variables ---------------------------------------------

/**
 * Rocket position
 */
var position = new THREE.Spherical(0,0,0);

/**
 * Vars for keydown events
 */
var left = false;
var up = false;
var right = false;
var down = false;


/**
 * Renderer
 */
const renderer = new THREE.WebGLRenderer({ antialias: true });


/**
 * Create Scene
 */
const scene = new THREE.Scene();


/**
 * Earth's radius
 */
const R = 2;


/**
 * Velocity Variables
 */
const velocityShip = 1;

/**
 * Axes helper
 */
const axesHelper = new THREE.AxesHelper(R + 2);
axesHelper.visible = true;
scene.add(axesHelper);


/**
 * Create Cameras
 */
// Global val for the current camera
var camera;
// Perspective 
var perspectiveCamera;
var ortographicCamera;
var rocketshipCamera;

var cameraKey;

/**
 * Texture Loader
 */
const textureLoader = new THREE.TextureLoader();


/**
 * Clock
 */
const clock = new THREE.Clock();
// Aux var for delta calculation
var t = 0;


/**
 * Materials for all objects
 */
const materialBlue = new THREE.MeshBasicMaterial({ color: 0x0d3790 });
const materialGrey = new THREE.MeshBasicMaterial({ color: 0xc2c2b3 });
const materialDarkBrown = new THREE.MeshBasicMaterial({ color: 0x523a26 });
const materialDarkGreen = new THREE.MeshBasicMaterial({ color: 0xa6865 });
const materialYellow = new THREE.MeshBasicMaterial({ color: 0xedbd46 });
const materialWhite = new THREE.MeshBasicMaterial({ color: 0xFFFFFF });
const materialRed = new THREE.MeshBasicMaterial({ color: 0xFF0000 });


/**
 * Arrays with space garbage. Each array has all points that satisfy their conditions
 */
// x >= 0, y >= 0, z >= 0
const px_py_pz = [];
// x >= 0, y >= 0, z < 0
const px_py_nz = [];
// x >= 0, y < 0, z >= 0
const px_ny_pz = [];
// x >= 0, y < 0, z < 0
const px_ny_nz = [];
// x < 0, y >= 0, z >= 0
const nx_py_pz = [];
// x < 0, y >= 0, z < 0
const nx_py_nz = [];
// x < 0, y < 0, z >= 0
const nx_ny_pz = [];
// x < 0, y < 0, z < 0
const nx_ny_nz = [];


/**
 * Rocketship var declaration
 */
const rocket = new THREE.Object3D();



// --------------------------- Aux functions ---------------------------------------------
/**
 * Creates a sphere mesh and adds it to scene
 * @param {number} radius 
 * @param {Material} material 
 * @param {Array} position
 * @returns Sphere Mesh
 */
function createSphere(radius, material, position) {
    'use strict';

    let geometry = new THREE.SphereGeometry(radius, 64, 32);
    let sphere = new THREE.Mesh(geometry, material);
    sphere.position.set(position[0], position[1], position[2]);
    scene.add(sphere);
    return sphere;
}


/**
 * Creates a cylinder mesh and adds it to the seen
 * @param {number} radiusTop 
 * @param {number} radiusBottom 
 * @param {number} height 
 * @param {Material}} material 
 * @param {Array} position 
 * @returns
 */
function createCylinder(radiusTop, radiusBottom, height, material, position) {
    'use strict';

    let geometry = new THREE.CylinderGeometry(radiusTop, radiusBottom, height,64);
    let cylinder = new THREE.Mesh(geometry, material);
    cylinder.position.set(position[0], position[1], position[2]);
    scene.add(cylinder);
    return cylinder;
}


/**
 * Creates a capsule mesh and adds it to the seen
 * @param {number} radius 
 * @param {number} height 
 * @param {Material} material 
 * @param {Array} position 
 * @returns 
 */
function createCapsule(radius, height, material, position) {
    'use strict';

    let geometry = new THREE.CapsuleGeometry(radius, height);
    let capsule = new THREE.Mesh(geometry, material);
    capsule.position.set(position[0], position[1], position[2]);
    scene.add(capsule);
    return capsule;
}


/**
 * Creates a box mesh and adds it to the seen
 * @param {number} width 
 * @param {number} height 
 * @param {number} depth 
 * @param {Material} material 
 * @param {Array} position 
 * @returns 
 */
function createBox(width, height, depth, material, position) {
    'use strict';

    let geometry = new THREE.BoxGeometry(width, height, depth);
    let box = new THREE.Mesh(geometry, material);
    box.position.set(position[0], position[1], position[2]);
    scene.add(box);
    return box;
}


/**
 * Creates a cone mesh and adds it into the seen
 * @param {number} radius 
 * @param {number} height 
 * @param {Material} material 
 * @param {Array} position 
 * @returns 
 */
function createCone(radius, height, material, position) {
    'use strict';

    let geometry = new THREE.ConeGeometry(radius, height);
    let cone = new THREE.Mesh(geometry, material);
    cone.position.set(position[0], position[1], position[2]);
    scene.add(cone);
    return cone;
}


/**
 * Creates a dodecahedron mesh and adds it to the scene
 * @param {number} radius 
 * @param {Material} material 
 * @param {Array} position 
 * @returns 
 */
function createDodecahedron(radius, material, position) {
    'use strict';

    let geometry = new THREE.DodecahedronGeometry(radius);
    let dodecahedron = new THREE.Mesh(geometry, material);
    dodecahedron.position.set(position[0], position[1], position[2]);
    scene.add(dodecahedron);
    return dodecahedron;
}


/**
 * Creates a icosahedron mesh and adds it to the scene
 * @param {number} radius 
 * @param {Material} material 
 * @param {Array} position 
 * @returns 
 */
function createIcosahedron(radius, material, position) {
    'use strict';

    let geometry = new THREE.IcosahedronGeometry(radius);
    let icosahedron = new THREE.Mesh(geometry, material);
    icosahedron.position.set(position[0], position[1], position[2]);
    scene.add(icosahedron);
    return icosahedron;
}


/**
 * Gets a random number between an interval
 * @param {number} min 
 * @param {number} max 
 * @returns number
 */
function randomIntFromInterval(min, max) { // min and max included 
    'use strict';
    return Math.random() * (max - min) + min;
}


/**
 * Gets random point in xyz that is radius distance from the center
 * @param {number} radius 
 * @returns array with 3 coordinates
 */
function randomSpherePoint(radius) {
    'use strict';

    let u = Math.random();
    let v = Math.random();
    let theta = 2 * Math.PI * u;
    let phi = Math.acos(2 * v - 1);
    let x = radius * Math.sin(phi) * Math.cos(theta);
    let y = radius * Math.sin(phi) * Math.sin(theta);
    let z = radius * Math.cos(phi);
    return [x, y, z];
}


/**
 * Adds object to respective array
 * @param {Mesh} object 
 * @param {Array} randPos 
 * @param {Array} array 
 * @return Correct array given the object's position
 */
function getArray(position) {
    'use strict';
    // x >= 0
    if (position.x >= 0) {
        // y >= 0
        if (position.y >= 0) {
            // z >= 0
            if (position.z >= 0) {
                return px_py_pz;
            }
            // z < 0
            else {
                return px_py_nz;
            }
        }
        // y < 0
        else {
            // z >= 0
            if (position.z >= 0) {
                return px_ny_pz;
            }
            // z < 0
            else {
                return px_ny_nz;
            }
        }
    }
    // x < 0
    else {
        // y >= 0
        if (position.y >= 0) {
            // z >= 0
            if (position.z >= 0) {
                return nx_py_pz;
            }
            // z < 0
            else {
                return nx_py_nz;
            }
        }
        // y < 0
        else {
            // z >= 0
            if (position.z >= 0) {
                return nx_ny_pz;
            }
            // z < 0
            else {
                return nx_ny_nz;
            }
        }
    }
}


/**
 * Create Ortographic camera
 */
function createOrtographicCamera() {
    'use strict';

    ortographicCamera = new THREE.OrthographicCamera(-window.innerWidth / 200,
        window.innerWidth / 200,
        window.innerHeight / 200,
        -window.innerHeight / 200, 0, 10
    );

    ortographicCamera.position.x = 0;
    ortographicCamera.position.y = 0;
    ortographicCamera.position.z = 2 * R;
    ortographicCamera.lookAt(scene.position);
}


/**
 * Create Perspective camera
 */
function createPerspectiveCamera() {
    'use strict';

    perspectiveCamera = new THREE.PerspectiveCamera(70, 
        window.innerWidth / window.innerHeight,
        1,
        10
    );
    
    perspectiveCamera.position.x = 2 * R;
    perspectiveCamera.position.y = 2 * R;
    perspectiveCamera.position.z = 2 * R;
    perspectiveCamera.lookAt(scene.position);
}


/**
 * Create Rocket ship camera
 */
function createRocketCamera() {
    'use strict';
    
    rocketshipCamera = new THREE.PerspectiveCamera(70,
        window.innerWidth / window.innerHeight,
        0.01,
        10
    );
    
    rocket.add(rocketshipCamera);
    rocketshipCamera.position.x = 0;
    rocketshipCamera.position.y = -1;
    rocketshipCamera.position.z = -1;
    rocketshipCamera.lookAt(rocket.position);
}


/**
 * Creates earth mesh and adds it to the scene
 */
function createEarth() {
    'use strict';
    createSphere(R, materialBlue, [0, 0, 0]);   
}


/**
 * Create Rockect ship mesh and andds it to the seen
 */
function createRocket() {
    'use strict';

    // Gets a random point 1.2*R away from the center
    let rand = randomSpherePoint(1.2 * R);
    // Rocket parts
    var rocketBody = createCylinder(0.05, 0.05, R / 18, materialWhite, [0,0,0]);
    // Nose height is it's altitude/2 + rocket body altitude/2 = R / 36 + R / 52 = (11R) / 234
    let rocketNose = createCylinder(0.001, 0.05, R / 26, materialRed, [0, ((11 * R) / 234), 0]);
    let prop1 = createCapsule(0.025, 0.02, materialGrey, [0, 0, 0.0525]);
    let prop2 = createCapsule(0.025, 0.02, materialGrey, [0, 0,- 0.0525]);
    let prop3 = createCapsule(0.025, 0.02, materialGrey, [0.0525, 0, 0]);
    let prop4 = createCapsule(0.025, 0.02, materialGrey, [-0.0525, 0, 0]);
    // Rocket ship
    rocket.add(rocketBody);
    rocket.add(rocketNose);
    rocket.add(prop1);
    rocket.add(prop2);
    rocket.add(prop3);
    rocket.add(prop4);
    // collision radius = nose height + body height/2
    rocket.collisonRadius = (35*R)/468;
    scene.add(rocket);

    rocket.position.set(rand[0],rand[1],rand[2]);
    
    position.setFromVector3(rocket.position);
}


/**
 * Creates and adds to the scene space garbage.
 * 3 Cubes, 3 Cones, 7 Dodecahedron and 7 Icosahedron
 */
function createSpaceGarbage() {
    'use strict';
    let array = [];

    // Create 3 cubes
    for (var i = 0; i < 3; i++) {
        let rand = randomIntFromInterval(R / 24, R / 20);
        let randPos = randomSpherePoint(1.2 * R);
        let cube = createBox(rand, rand, rand, materialDarkBrown, randPos);
        cube.collisonRadius = rand;
        array = getArray(cube.position);
        array.push(cube);
    }
    // Create 3 cones
    for (i = 0; i < 3; i++) {
        let rand = randomIntFromInterval(R / 24, R / 20);
        let randPos = randomSpherePoint(1.2 * R);
        let cone = createCone(rand, rand, materialDarkGreen, randPos);
        cone.collisonRadius = rand;
        array = getArray(cone.position);
        array.push(cone);
    }
    // Create 8 dodecahedrons
    for (i = 0; i < 8; i++) {
        let rand = randomIntFromInterval(R / 24, R / 20);
        let randPos = randomSpherePoint(1.2 * R);
        let dodecahedron = createDodecahedron(rand, materialYellow, randPos);
        dodecahedron.collisonRadius = rand;
        array = getArray(dodecahedron.position);
        array.push(dodecahedron);
    }
    // Create 8 icosahedrons
    for (i = 0; i < 8; i++) {
        let rand = randomIntFromInterval(R / 24, R / 20);
        let randPos = randomSpherePoint(1.2 * R);
        let icosahedron = createIcosahedron(rand, materialRed, randPos);
        icosahedron.collisonRadius = rand;
        array = getArray(icosahedron.position);
        array.push(icosahedron);
    }
}


/**
 * Function to rotate the rocket each frame
 * @param {number} delta 
 */
function rotateRocket(delta) {
    'use strict';
    let vector2 = new THREE.Vector2(0,0);
   
    if (left) {
       vector2.x -= 1;
    }

    if (up) {
        vector2.y -= 1;
    }

    if (right) {
        vector2.x += 1;
    }

    if (down) {
        vector2.y += 1;
    }

    vector2.normalize();
    vector2.multiplyScalar(velocityShip * delta);
    position.phi += vector2.y;
    position.theta += vector2.x;
    rocket.position.setFromSpherical(position);

    // If rocket moved, we need to update space direction
    if(left || right || up || down){
        let clonePosition = position.clone();
        clonePosition.phi += vector2.y * 2;
        clonePosition.theta += vector2.x * 2;

        rocket.up.setFromSpherical(clonePosition);
        rocket.lookAt(scene.position);
    }
}


/**
 * Detects and takes care of collisions
 */
function computeCollisions() {
    'use strict';

    let rocketWorldPosition = new THREE.Vector3();
    // Get rocket's position in scene
    rocket.getWorldPosition(rocketWorldPosition);
    // Gets array with garbage in rocke'ts quadrant
    let garbageVector = getArray(rocketWorldPosition);
    
    // Executes functuon through all objects at garbageVector
    garbageVector.forEach(garbageUnit => {
        let distance = rocketWorldPosition.distanceTo(garbageUnit.position);
        // Distance from rocket to garbage is less or equal to sum of booth radius
        if(garbageUnit.collisonRadius + rocket.collisonRadius >= distance){
            scene.remove(garbageUnit)
        }
    });

}


/**
 * Function to change camera if requested
 */
function changeCamera(){
    'use strict'
    if(cameraKey == 1){
        camera = ortographicCamera;
    }
    if(cameraKey == 2){
        camera = perspectiveCamera;
    }
    if(cameraKey == 3){
        camera = rocketshipCamera;
    }
}


// -------------------------------------- Main functions -------------------------------------------------


/**
 * Adjust window size when resized
 */
function onResize(){
    'use strict';

    renderer.setSize(window.innerWidth, window.innerHeight);
    
    if (window.innerHeight > 0 && window.innerWidth > 0) {
        camera.aspect = window.innerWidth / window.innerHeight;
        camera.updateProjectionMatrix();
    }
}


/**
 * Does something when certain keys are pressed
 */
function onKeyDown(e){
    'use strict';

    switch (e.keyCode) {
        case 49: // 1
            cameraKey = 1;
            break;
        case 50: // 2
            cameraKey = 2;
            break;
        case 51: // 3
            cameraKey = 3   ;
            break;
        case 37: // left
            left = true;
            break;
        case 38: // up
            up = true;
            break;
        case 39: // right
            right = true;
            break;
        case 40: // down
            down = true;
            break;
    }
}


/**
 * Does something when certain keys are unpressed
 */
function onKeyUp(e){
    'use strict';

    switch (e.keyCode) {
        case 37: // left
            left = false;
            break;
        case 38: // up
            up = false;
            break;
        case 39: // right
            right = false;
            break;
        case 40: // down
            down = false;
            break;
    }
}


/**
 * Function to initialize program
 */
 function init(){
    'use strict';
    renderer.setSize(window.innerWidth, window.innerHeight);
    document.body.appendChild(renderer.domElement);
    
    // Create ortographic camera
    createOrtographicCamera();
    // Create perspective camera
    createPerspectiveCamera();
    
    // Add Earth
    createEarth();
    // Add Rocket
    createRocket();
    // Add Space Garbage
    createSpaceGarbage();

    // Create rocket camera
    createRocketCamera();

    camera = ortographicCamera;    
    
    window.addEventListener("keydown", onKeyDown);
    window.addEventListener("keyup", onKeyUp);
    window.addEventListener("resize", onResize);
}


/**
 * Function to update scene
 */
 function animate(){
    'use strict';

    let now = clock.getElapsedTime();
    let delta = now - t;
    t = now;

    renderer.render(scene, camera);

    changeCamera();

    rotateRocket(delta);

    // Checks collisions and takes care of them
    computeCollisions();

    requestAnimationFrame(animate);
}